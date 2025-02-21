rm -rf myenv
python3 -m venv myenv
source myenv/bin/activate
pip install aiohttp aiofiles tabulate
python3 main.py