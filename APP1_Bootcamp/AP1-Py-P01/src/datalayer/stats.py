import json
from pathlib import Path
from utils.utils import get_project_root

class RogueStats:
    __instance = None
    __save_dir = get_project_root() / "datasets/saves"
    __stats_dir = get_project_root() / "datasets/stats"
    __stats_file = "stats.json"
    __save_file = "saves.json"

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls)

        return cls.__instance

    def __init__(self):
        self.nickname = "Guest"
        self.gold: int = 0
        self.rogue_level: int = 1
        self.defeated_enemies: int = 0
        self.eaten_food: int = 0
        self.used_potions: int = 0
        self.used_scrolls: int = 0
        self.total_hits: int = 0
        self.missed_hits: int = 0
        self.passed_cells: int = 0

    @classmethod
    def get_instance(cls): return cls.__instance

    def __get_stats_file(self) -> Path:
        if not self.__stats_dir.exists():
            raise FileExistsError(f"Stats directory does not exist: {self.__stats_dir}")
        for f in self.__stats_dir.iterdir():
            if f.name == self.__stats_file: return f
        f_path = self.__stats_dir / self.__stats_file
        f_path.touch()
        return f_path

    def __get_save_file(self) -> Path:
        if not self.__save_dir.exists():
            raise FileExistsError(f"Save directory does not exist: {self.__save_dir}")
        for f in self.__save_dir.iterdir():
            if f.name == self.__save_file: return f
        f_path = self.__save_dir / self.__save_file
        f_path.touch()
        return f_path

    def form_stats_dict(self) -> dict:
        return {
            "last_record": True,
            "Никнейм": self.nickname,
            "Золото": self.gold,
            "Уровень подземелья": self.rogue_level,
            "Поверженные враги": self.defeated_enemies,
            "Съеденной еды": self.eaten_food,
            "Использованных зелий": self.used_potions,
            "Использованных свитков": self.used_scrolls,
            "Нанесенных ударов": self.total_hits,
            "Промахов": self.missed_hits,
            "Пройденных клеток": self.passed_cells,
        }

    def check_nickname(self, nickname: str) -> bool:
        stats_file = self.__get_stats_file()
        try:
            with stats_file.open(mode="r", encoding="utf-8") as rd_f:
                data = json.load(rd_f)
                for dct in data:
                    if dct["Никнейм"] == nickname: return False
        except json.JSONDecodeError: return True
        except FileNotFoundError as e: raise e
        return True

    def get_sorted_stats(self) -> list[dict]:
        stats_file = self.__get_stats_file()
        data = []
        try:
            with stats_file.open(mode="r", encoding="utf-8") as rd_f:
                data = json.load(rd_f)
                data.sort(key=lambda dct: dct.get("Золото", 0), reverse=True)
        except json.JSONDecodeError: pass
        except FileNotFoundError as e: raise e
        return data

    def dump_json_stats(self):
        stats_file = self.__get_stats_file()
        try:
            with stats_file.open(mode="r", encoding="utf-8") as rd_f:
                data = json.load(rd_f)
        except json.JSONDecodeError: data = []
        except FileNotFoundError as e: raise e
        for dct in data:
            dct["last_record"] = False
        data.append(self.form_stats_dict())
        try:
            with stats_file.open(mode="w", encoding="utf-8") as wr_f:
                json.dump(data, wr_f, ensure_ascii=False, indent=4)
        except FileNotFoundError as e: raise e

    def __form_current_state_dict(self) -> dict:
        from domain.objects.character import Character
        return {"nickname": self.nickname, "stats": self._dump(), "character_state": Character.get_instance()._dump()}

    def dump_json_save(self):
        save_file = self.__get_save_file()
        try:
            with save_file.open(mode="w", encoding="utf-8") as wr_f:
                json.dump(self.__form_current_state_dict(), wr_f, ensure_ascii=False, indent=4)
        except Exception as e: raise e

    def load_json_save(self) -> dict:
        save_file = self.__get_save_file()
        try:
            with save_file.open(mode="r", encoding="utf-8") as rd_f:
                data = json.load(rd_f)
        except json.JSONDecodeError: data = {}
        except FileNotFoundError as e: raise e
        return data

    def remove_save(self):
        if not self.__save_dir.exists():
            raise FileExistsError(f"Save directory does not exist: {self.__save_dir}")

        for f in self.__save_dir.iterdir():
            if f.name == self.__save_file: f.unlink()

    def _dump(self):
        return {
            "nickname": self.nickname,
            "gold": self.gold,
            "rogue_level": self.rogue_level,
            "defeated_enemies": self.defeated_enemies,
            "eaten_food": self.eaten_food,
            "used_potions": self.used_potions,
            "used_scrolls": self.used_scrolls,
            "total_hits": self.total_hits,
            "missed_hits": self.missed_hits,
            "passed_cells": self.passed_cells,
        }

    def _load(self, **kwargs):
        self.nickname = kwargs["nickname"]
        self.gold = kwargs["gold"]
        self.rogue_level = kwargs["rogue_level"]
        self.defeated_enemies = kwargs["defeated_enemies"]
        self.eaten_food = kwargs["eaten_food"]
        self.used_potions = kwargs["used_potions"]
        self.used_scrolls = kwargs["used_scrolls"]
        self.total_hits = kwargs["total_hits"]
        self.missed_hits = kwargs["missed_hits"]
        self.passed_cells = kwargs["passed_cells"]
        