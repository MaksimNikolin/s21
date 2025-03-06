from random import choice, randint
from typing import Any
from domain import Coordinate
from domain.objects.character import Character
from domain.objects.enemies.enemy import Enemy
from utils.logger import domain_log

class Key:
    symbol = "§"
    __info_map = {16: "red", 17: "green", 18: "blue"}

    def __init__(self, color):
        self.color = color + 3
        self.info = self.__info_map[color]

class Door:
    base_symbol, base_color = "#", 6

    def __init__(self, room, crd: Coordinate):
        self.room = room
        self.crd = crd
        self.symbol = self.base_symbol
        self.color = self.base_color
        self.lock = False

    @property
    def is_open(self): return not self.lock

    @property
    def is_closed(self): return self.lock

class Corridor:
    corridor_symbol = "."
    empty_symbol = " "
    color = 6

    def __init__(self, start_door: Door, finish_door: Door, direction: str):
        self.__doors = {
            start_door.crd: start_door,
            finish_door.crd: finish_door,
        }
        self.__corridor: dict[Coordinate, Any] = {}
        self.__objects: dict[Coordinate, Any] = {}
        self.__items: dict[Coordinate, Any] = {}
        self.start, self.finish = self.__shift_initials(start_door.crd, finish_door.crd, direction)
        self.__generate_corridor(direction)
        self.has_character = False
        self.__visited = False
        domain_log.info("{cls} initialized", cls=self.__class__.__name__)

    @property
    def doors(self): return self.__doors

    @staticmethod
    def __shift_initials(start: Coordinate, finish: Coordinate, direction: str) -> tuple[Coordinate, Coordinate]:
        y, x = start
        y_, x_ = finish
        if direction == "v":
            if y > y_: new_s, new_f = (y - 1, x), (y_ + 1, x_)
            else: new_s, new_f = (y + 1, x), (y_ - 1, x_)
        elif direction == "h":
            if x > x_: new_s, new_f = (y, x - 1), (y_, x_ + 1)
            else: new_s, new_f = (y, x + 1), (y_, x_ - 1)
        else: raise ValueError("incorrect direction")
        return new_s, new_f

    def __generate_corridor(self, direction: str):
        y, x = self.start
        y_, x_ = self.finish
        if direction == "v":
            domain_log.info("Generating vertical corridor")
            if x == x_:
                self.__build_vertical_corridor(y, y_, x)
            else:
                y_turn = randint(min(y, y_), max(y, y_))
                self.__build_vertical_corridor(y, y_turn, x)
                self.__build_horizontal_corridor(x, x_, y_turn)
                self.__build_vertical_corridor(y_, y_turn, x_)
        elif direction == "h":
            domain_log.info("Generating horizontal corridor")
            if y == y_:
                self.__build_horizontal_corridor(x, x_, y)
            else:
                x_turn = randint(min(x, x_), max(x, x_))
                self.__build_horizontal_corridor(x, x_turn, y)
                self.__build_vertical_corridor(y, y_, x_turn)
                self.__build_horizontal_corridor(x_, x_turn, y_)

    def __build_vertical_corridor(self, y1: int, y2: int, x: int):
        for y in range(min(y1, y2), max(y1, y2) + 1):
            self.__corridor[y, x] = self.corridor_symbol

    def __build_horizontal_corridor(self, x1: int, x2: int, y: int):
        for x in range(min(x1, x2), max(x1, x2) + 1):
            self.__corridor[y, x] = self.corridor_symbol

    def get_cell(self, y: int, x: int) -> tuple[str, int]:
        crd = (y, x)
        if crd in self.__objects and self.__objects[crd].is_visible:
            return self.__objects[crd].symbol, self.__objects[crd].color
        if crd in self.__items: return self.__items[crd].symbol, self.__items[crd].color
        if crd in self.__doors: return self.__doors[crd].symbol, self.__doors[crd].color
        return self.__corridor[crd], self.color

    def is_in(self, crd: Coordinate) -> bool:
        return crd in self.__corridor or (crd in self.__doors and self.__doors[crd].is_open)

    def is_in_visible(self, crd: Coordinate) -> bool:
        return crd in self.__corridor or crd in self.__doors

    def is_in_and_available_for_move(self, crd: Coordinate) -> bool:
        return (crd in self.__corridor or (crd in self.__doors and self.__doors[crd].is_open)) and crd not in self.__objects

    def is_in_and_available(self, crd: Coordinate) -> bool:
        return (crd in self.__corridor or crd in self.__doors) and crd not in self.__objects and crd not in self.__items

    def get_random_crd_in_zone(self, crd: Coordinate, radius: int) -> Coordinate:
        if not radius:
            y_, x_ = choice(list(self.__corridor))
            while (y_, x_) in self.__objects or (y_, x_) in self.__items:
                y_, x_ = choice(list(self.__corridor))
            return y_, x_
        y, x = crd
        available_cord = []
        for cor_crd in self.__corridor:
            if cor_crd in self.__objects or cor_crd in self.__items: continue
            if y - radius <= cor_crd[0] <= y + radius and x - radius <= cor_crd[1] <= x + radius:
                available_cord.append(cor_crd)
        return choice(available_cord)

    def add_object(self, crd: Coordinate, obj: Character | Enemy): self.__objects[crd] = obj

    def remove_object(self, crd: Coordinate): del self.__objects[crd]

    def get_object(self, crd: Coordinate) -> Character | Enemy | None: return self.__objects.get(crd)

    @property
    def objects(self): return self.__objects.copy()

    def add_item(self, crd: Coordinate, obj: Any): self.__items[crd] = obj

    def remove_item(self, crd: Coordinate): del self.__items[crd]

    def get_item(self, crd: Coordinate) -> Any | None: return self.__items.get(crd)

    def face_door(self, crd: Coordinate):
        if crd in self.__doors and self.__doors[crd].is_closed: return self.__doors[crd]
        return None
