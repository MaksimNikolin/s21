from random import choice
from time import sleep
from datalayer.stats import RogueStats
from domain import Coordinate
from domain.map.corridor import Corridor, Door
from domain.map.keys import generate_locked_doors
from domain.map.room import Room
from domain.objects.character import Character
from domain.objects.enemies.enemy import Enemy
from domain.objects.items.item import Item
from domain.objects.utils import MovePattern, RogueEvent
# from utils.logger import domain_log


class LevelMap:
    __map_symbol = " "
    __map_color = 1
    __corridor_color = Corridor.color

    def __init__(self, height: int, width: int, level: int, complexity_coef: float):
        self.height = height
        self.width = width
        self.y, self.x, self.y_, self.x_ = 0, 0, self.height - 1, self.width - 1
        self.__character = self.__get_character()
        self.__rooms = self.__generate_level_rooms()
        self.__corridors: list[Corridor] = []
        self.__generate_doors_and_corridors()
        self.__place_character_to_initial_room()
        generate_locked_doors(self)
        self.__place_exit()
        self.__generate_enemies(level, complexity_coef)
        self.__generate_items(level, complexity_coef)
        self.__visited_corridors = set()
        # domain_log.info("{cls} initialized", cls=self.__class__.__name__)

    @property
    def rooms(self): return self.__rooms

    def __get_character(self) -> Character:
        # if not ch:
        #     domain_log.error("{cls} failed to get character", cls=self.__class__.__name__)
        #     raise AttributeError("Please create a character before LevelMap initializing.")
        return Character.get_instance()

    def __generate_level_rooms(self) -> list[Room]:
        rooms = []
        w_size = self.width // 3
        h_size = self.height // 3
        w_step = w_size - 1
        h_step = h_size - 1
        room_id = 0
        for col in range(3):
            for row in range(3):
                rooms.append(Room(self.x + w_step * row, self.y + h_step * col, h_size, w_size, room_id))
                room_id += 1
        return rooms

    def __place_character_to_initial_room(self): choice(self.__rooms).place_character()

    def __place_exit(self): choice(list(filter(lambda r: not r.has_character, self.__rooms))).place_exit()

    def __generate_doors_and_corridors(self):
        room_id, cur_group = 0, 0
        room_groups = [set()]

        def gen_doors_and_corridor(id_: int, side_: str) -> int:
            next_id_, next_busy_side, start_coord = self.__rooms[id_].generate_door(side_)
            start_door = self.__rooms[id_].add_actual_door(self.__rooms[next_id_], start_coord)
            _, _, finish_coord = self.__rooms[next_id_].generate_door(next_busy_side)
            finish_door = self.__rooms[next_id_].add_actual_door(self.__rooms[id_], finish_coord)
            # domain_log.info(
            #     "Generating a new corridor: room_id={id}, next_id={n_id}, initial_side={side}",
            #     id=id_,
            #     n_id=next_id_,
            #     side=side_,
            # )
            self.__corridors.append(Corridor(start_door, finish_door, direction="v" if side_ in ["U", "D"] else "h"))
            return next_id_

        def union_groups():
            nonlocal room_groups
            for i in range(len(room_groups) - 1):
                for j in range(i + 1, len(room_groups)):
                    if room_groups[i] & room_groups[j]: room_groups[i] |= room_groups[j]
                        # domain_log.info("Corridor groups are united")

        def check_connections() -> bool:
            nonlocal room_groups
            return all(room_groups[0] & room_groups[i] for i in range(1, len(room_groups)))

        def add_connection():
            nonlocal room_groups
            for i in range(1, len(room_groups)):
                if not room_groups[0] & room_groups[i]: 
                    id_ = choice(list(room_groups[i]))
                    # domain_log.warning("Adding new connection for room {id}", id=id_)
                    for door in self.__rooms[id_].random_door_sides():
                        room_groups[i].add(gen_doors_and_corridor(id_, door))

        visited_rooms = [False for _ in self.__rooms]
        while not all(visited_rooms):
            visited_rooms[room_id] = True
            next_id = -1
            for side in self.__rooms[room_id].random_door_sides():
                next_id = gen_doors_and_corridor(room_id, side)
                room_groups[cur_group].add(room_id)
                visited_rooms[next_id] = True
                room_groups[cur_group].add(next_id)

            if next_id == -1:
                # domain_log.warning("Random doors generation: adding new group")
                room_id = visited_rooms.index(False)
                room_groups.append(set())
                cur_group += 1
                continue
            room_id = next_id

        union_groups()
        while not check_connections():
            # domain_log.warning("Found a rooms group without direct connection")
            add_connection()
            union_groups()

    def __generate_enemies(self, level: int, coef: float):
        for room in self.__rooms:
            if room.has_character: continue
            room.generate_enemies(level, coef)

    def __generate_items(self, level: int, coef: float):
        for room in self.__rooms:
            room.generate_items(level, coef)
            room.generate_keys()

    def move_character(self, direction: str) -> list[RogueEvent]:
        events, able_to_move = self.__character.check_object_effects()
        if not able_to_move: return events
        y, x = self.__character.get_crd()
        match direction:
            case "w": y -= 1
            case "s": y += 1
            case "a": x -= 1
            case "d": x += 1
            case _: raise ValueError(f"Invalid direction {direction}")
        # domain_log.info("Moving character: {d}", d=direction)
        events.extend(self.__move_character((y, x)))
        return events

    def __move_character(self, crd: Coordinate) -> list[RogueEvent]:
        for place in self.__rooms + self.__corridors:
            if place.is_in(crd) or place.face_door(crd):
                # domain_log.info(f"Moving character in {place.__class__.__name__}")
                return self.__move_actor(place, crd)
        return []

    def __move_actor(self, place: Room | Corridor, crd: Coordinate) -> list[RogueEvent]:
        events = []
        if place.get_object(crd):
            # domain_log.info("Character faced an enemy")
            events.extend(self.__attack_enemy(place, crd))
            return events

        if door := place.face_door(crd):
            events.append(self.__knock_the_door(door))
            return events

        if isinstance(place, Room) and place.get_exit(crd):
            events.append(RogueEvent("Вы нашли выход"))

        if place.get_item(crd):
            # domain_log.info("Character found item")
            events.extend(self.__pick_up_item(place, crd))

        if isinstance(place, Room) and (key := place.get_key(crd)):
            events.append(RogueEvent(f"Вы нашли {key.info} ключ", key.color))

        self.__remove_character()
        place.has_character = True
        place.add_object(crd, self.__character)
        self.__character.place(crd)
        RogueStats.get_instance().passed_cells += 1
        return events

    def __knock_the_door(self, door: Door):
        character = Character.get_instance()
        if door.color in character.keys:
            door.lock = False
            character.keys.remove(door.color)
            door.color = Door.base_color
            return RogueEvent("Вы открыли дверь с помощью ключа")
        return RogueEvent("Дверь заперта. Найдите подходящий ключ")

    def __remove_character(self):
        for obj in self.__rooms + self.__corridors:
            if obj.has_character:
                obj.has_character = False
                obj.remove_object(self.__character.get_crd())
                break

    def __attack_enemy(self, place: Room | Corridor, crd: Coordinate) -> list[RogueEvent]:
        events, exp = place.get_object(crd).harm(*self.__character.attack())
        if exp:
            place.remove_object(crd)
            events.extend(self.__character.add_experience(exp))
            RogueStats.get_instance().defeated_enemies += 1
        return events

    def __pick_up_item(self, place: Room | Corridor, crd: Coordinate) -> list[RogueEvent]:
        events, picked_up = self.__character.pick_up_item(place.get_item(crd))
        if picked_up: place.remove_item(crd)
        return events

    def __is_point_visible(self, crd: Coordinate) -> bool:
        y1, x1 = crd
        y2, x2 = self.__character.get_crd()
        dy, dx = abs(y2 - y1), abs(x2 - x1)
        n = 1 + dx + dy
        x_dir = 1 if x2 > x1 else -1
        y_dir = 1 if y2 > y1 else -1
        err = dx - dy
        dx *= 2
        dy *= 2
        x, y = x1, y1
        for _ in range(n):
            if not any(obj.is_in((y, x)) for obj in self.__rooms + self.__corridors):
                for corridor in self.__corridors:
                    if crd in corridor.doors and crd == (y, x): break
                else: return False
            if err > 0:
                x += x_dir
                err -= dy
            else:
                y += y_dir
                err += dx
        return True

    def make_rogue_move(self) -> tuple[list[RogueEvent], bool]:
        events = []
        alive, cur_alive = True, True
        for crd, obj, place in [
            (crd, obj, place_)
            for place_ in self.__rooms + self.__corridors
            for crd, obj in place_.objects.items()
            if not isinstance(obj, Character)
        ]:
            eff_events, able_to_move = obj.check_object_effects()
            events.extend(eff_events)
            if not able_to_move: continue
            if obj.is_engaged(crd) and (obj.status_engaged() or self.__is_point_visible(crd)):
                # domain_log.info(f"{obj.__class__.__name__} is chasing Character!")
                obj.set_engaged_status()
                g_events, cur_alive = self.__engaged_enemy_move(place, crd, obj)
                events.extend(g_events)
            else:
                # domain_log.info(f"{obj.__class__.__name__} makes a pattern move")
                self.__casual_enemy_move(place, crd, obj)
            alive = cur_alive if alive else alive
        return events, alive

    def __casual_enemy_move(self, place: Room | Corridor, crd: Coordinate, enemy: Enemy):
        if enemy.pattern == MovePattern.STANDARD: self.__make_standard_move(place, crd, enemy)
        elif enemy.pattern == MovePattern.DIAGONAL: self.__make_diagonal_move(place, crd, enemy)
        elif enemy.pattern == MovePattern.JUMP: self.__make_jump_move(place, crd, enemy)
        elif enemy.pattern == MovePattern.ITEM: pass
        else:
            # domain_log.error("Unknown move pattern")
            raise NotImplementedError("Unknown move pattern")

    def __make_standard_move(self, place: Room | Corridor, crd: Coordinate, enemy: Enemy):
        if enemy.speed <= 0:
            # domain_log.error("Enemy speed cannot be 0 for STANDARD move pattern")
            raise ValueError("Enemy speed cannot be 0 for STANDARD move pattern")
        y, x = crd
        options = []

        def is_in_place(crd: Coordinate): return any(obj.is_in_and_available_for_move(crd) for obj in self.__rooms + self.__corridors)

        for x_ in range(x - enemy.speed, x):
            if not is_in_place((y, x_)): break
            options.append((y, x_))

        for x_ in range(x + 1, x + enemy.speed + 1):
            if not is_in_place((y, x_)): break
            options.append((y, x_))

        for y_ in range(y - enemy.speed, y):
            if not is_in_place((y_, x)): break
            options.append((y_, x))

        for y_ in range(y + 1, y + enemy.speed + 1):
            if not is_in_place((y_, x)): break
            options.append((y_, x))

        if not options: return self.__replace_enemy_on_map(place, crd, choice(options), enemy)

    def __make_diagonal_move(self, place: Room | Corridor, crd: Coordinate, enemy: Enemy):
        if enemy.speed <= 0:
            # domain_log.error("Enemy speed cannot be 0 for DIAGONAL move pattern")
            raise ValueError("Enemy speed cannot be 0 for DIAGONAL move pattern")

        if isinstance(place, Corridor): 
            self.__make_standard_move(place, crd, enemy)
            return

        y, x = crd
        options = []
        ur, ul, dr, dl = True, True, True, True
        for i in range(1, enemy.speed + 1):
            if dr and any(obj.is_in_and_available_for_move((y + i, x + i)) for obj in self.__rooms + self.__corridors):
                options.append((y + i, x + i))
            else: dr = False
            if ur and any(obj.is_in_and_available_for_move((y - i, x + i)) for obj in self.__rooms + self.__corridors):
                options.append((y - i, x + i))
            else: ur = False
            if ul and any(obj.is_in_and_available_for_move((y - i, x - i)) for obj in self.__rooms + self.__corridors):
                options.append((y - i, x - i))
            else: ul = False
            if dl and any(obj.is_in_and_available_for_move((y + i, x - i)) for obj in self.__rooms + self.__corridors):
                options.append((y + i, x - i))
            else: dl = False

        if not options:
            return self.__replace_enemy_on_map(place, crd, choice(options), enemy)

    def __engaged_enemy_move(self, place: Room | Corridor, crd: Coordinate, enemy: Enemy) -> tuple[list[RogueEvent], bool]:
        events = []
        alive = True
        y, x = crd
        possible_moves = [(y, x + 1), (y, x - 1), (y + 1, x), (y - 1, x)]
        if self.__character.get_crd() in possible_moves:
            sleep(0.2)
            # domain_log.info(f"{enemy.__class__.__name__} attacks Character!")
            g_events, alive = self.__character.harm(*enemy.attack())
            events.extend(g_events)
        else:
            # domain_log.info(f"{enemy.__class__.__name__} chases Character!")
            c_y, c_x = self.__character.get_crd()
            min_dist = (abs(y - c_y) ** 2 + abs(x - c_x) ** 2) + 2
            best_move = []
            for crd_ in possible_moves:
                if not any(obj.is_in_and_available_for_move(crd_) for obj in self.__rooms + self.__corridors): continue
                y_, x_ = crd_
                if (new_dist := (abs(c_x - x_) ** 2 + abs(c_y - y_) ** 2)) <= min_dist:
                    if new_dist < min_dist and best_move: best_move.pop()
                    min_dist = new_dist
                    best_move.append((y_, x_))
            if best_move: self.__replace_enemy_on_map(place, crd, choice(best_move), enemy)
        return events, alive

    def __replace_enemy_on_map(self, place: Room | Corridor, crd: Coordinate, new_crd: Coordinate, enemy: Enemy):
        if place.is_in(new_crd):
            place.add_object(new_crd, enemy)
            place.remove_object(crd)
        else:
            for new_place in self.__rooms + self.__corridors:
                if new_place.is_in(new_crd):
                    new_place.add_object(new_crd, enemy)
                    place.remove_object(crd)
                    break

    @staticmethod
    def __make_jump_move(place: Room | Corridor, crd: Coordinate, enemy: Enemy) -> None:
        actual_move_crd = place.get_random_crd_in_zone(crd, enemy.speed)
        place.add_object(actual_move_crd, enemy)
        place.remove_object(crd)

    def is_exit(self) -> bool:
        crd = self.__character.get_crd()
        for room in self.__rooms:
            if room.is_in(crd): return room.is_exit(crd)
        return False

    def get_cell(self, y: int, x: int) -> tuple[str, int]:
        crd = (y, x)
        for corridor in self.__corridors:
            if corridor.is_in_visible(crd):
                if self.__is_character_near(crd) and self.__is_point_visible(crd):
                    self.__visited_corridors.add(crd)
                    return corridor.get_cell(y, x)
                if crd in self.__visited_corridors:
                    return self.__map_symbol, self.__corridor_color

        for room in self.__rooms:
            if room.is_in(crd) and (room.has_character or (self.__is_character_near(crd) and self.__is_point_visible(crd))):
                return room.get_cell(y, x)
            if room.visited:
                sym, col = room.get_border_symbol(y, x)
                if sym:
                    return sym, col
                if room.is_exit(crd):
                    return room.get_cell(y, x)
        return self.__map_symbol, self.__map_color

    def __is_character_near(self, crd: Coordinate) -> bool:
        visibility = 3
        return (
            abs(crd[0] - self.__character.get_crd()[0]) <= visibility
            and abs(crd[1] - self.__character.get_crd()[1]) <= visibility
        )

    def drop_item(self, item: Item | None):
        if item:
            y_c, x_c = self.__character.get_crd()
            y, x = y_c - 1, x_c - 1

            def place(y_, x_) -> bool:
                nonlocal item
                for obj in self.__rooms + self.__corridors:
                    if obj.is_in_and_available((y_, x_)):
                        obj.add_item((y_, x_), item)
                        return True
                return False

            step, direction, turn = 0, 0, 2
            while y <= self.height and x <= self.width:
                if place(y, x):
                    # domain_log.info(f"{item.__class__.__name__} dropped item.")
                    break

                if step == turn:
                    if direction == 3: direction = 0
                    else:
                        direction += 1
                        if direction == 3 or (direction == 1 and turn > 2): turn += 1
                    step = 0

                if direction == 0: x += 1
                elif direction == 1: y += 1
                elif direction == 2: x -= 1
                elif direction == 3: y -= 1
                step += 1
