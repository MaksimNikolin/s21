from random import choice, sample
from enum import Enum
from domain.map.corridor import Door
from domain.map.room import Room
from domain.objects.character import Character

class DoorsColor(Enum):
    RED = 16
    GREEN = 17
    BLUE = 18

def generate_locked_doors(level_map):
    Character.get_instance().keys = []
    colors = (DoorsColor.RED, DoorsColor.GREEN, DoorsColor.BLUE)
    keys_amt = len(colors)

    all_doors: list[Door] = []
    for room in level_map.rooms:
        all_doors.extend(room.doors)
        if room.has_character:
            start_room = room
    locked_doors = sample(all_doors, keys_amt)
    lock_doors(locked_doors, colors)

    for _ in range(keys_amt):
        keys, available_rooms = [], []
        get_available_rooms(keys, available_rooms, start_room)
        key = keys.pop()
        place_key(available_rooms, key)
        for door in locked_doors:
            if door.color == key.value:
                door.lock = False
                door.color = Door.base_color
    lock_doors(locked_doors, colors)

def lock_doors(doors_to_lock, colors):
    for i, door in enumerate(doors_to_lock):
        door.lock = True
        door.color = colors[i].value

def place_key(available_rooms: list[Room], key: DoorsColor):
    room = choice(available_rooms)
    room.has_keys.append(key.value)

def get_available_rooms(keys: list[DoorsColor], available_rooms: list[Room], room: Room):
    available_rooms.append(room)
    for door in room.doors:
        door_ = get_2nd_door(room, door)
        closed_door = get_closed_door(door, door_)
        if not closed_door and door.room not in available_rooms:
            get_available_rooms(keys, available_rooms, door.room)
        elif closed_door and DoorsColor(closed_door.color) not in keys:
            keys.append(DoorsColor(door.color if door.is_closed else door_.color))

def get_2nd_door(room: Room, door_: Door):
    for door in door_.room.doors:
        if door.room == room: return door
    return None

def get_closed_door(door1: Door, door2: Door) -> None | Door:
    if door1.is_closed: return door1
    if door2.is_closed: return door2
    return None
