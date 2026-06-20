import os
import subprocess
import tarfile
import sys

venv_name = "daisymal"
requirements_file = "requirements.txt"
archive_name = f"{venv_name}.tar.gz"

def install_requirements():
    pip_path = os.path.join(venv_name, "bin", "pip")
    if not os.path.exists(pip_path):
        print("Incorrect venv")
        sys.exit(1)

    if not os.path.exists(requirements_file):
        print("File requirements not found")
        sys.exit(1)

    try:
        subprocess.run([pip_path, "install", "-r", requirements_file], check=True)
    except subprocess.CalledProcessError:
        print("Something wrong with installing")
        sys.exit(1)

def archive_venv():
    try:
        with tarfile.open(archive_name, "w:gz") as tar:
            tar.add(venv_name, arcname=os.path.basename(venv_name))
    except Exception as e:
        print("Something wrong with archiving")
        sys.exit(1)

def main():
    install_requirements()
    archive_venv()

if __name__ == "__main__":
    main()
