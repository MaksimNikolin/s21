#!/usr/bin/env python3

import os

def print_venv():
    venv = os.environ.get("VIRTUAL_ENV")
    if venv:
        print(f"Your current virtual env is {venv}")
    else:
        print("No active venv")

if __name__ == "__main__":
    print_venv()
    