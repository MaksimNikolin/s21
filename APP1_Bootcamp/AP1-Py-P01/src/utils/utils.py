from pathlib import Path


def get_project_root() -> Path:
    path_ = Path(__file__).parent
    while path_.name != "src":
        path_ = path_.parent

    return path_.parent
