import aiohttp
import aiofiles
import os
import asyncio
from tabulate import tabulate

async def download_image(session, url, save_path):
    flag = "Ошибка"
    try:
        async with session.get(url) as response:
            if response.status == 200:
                file_name = os.path.join(save_path, url.split("/")[-1])
                async with aiofiles.open(file_name, 'wb') as f:
                    await f.write(await response.read())
                flag = "Успех"
            return url, flag
    except Exception as e: return url, flag

async def get_images():
    save_path = input()
    while not os.path.exists(save_path) or not os.access(save_path, os.W_OK):
        print("Некорректный путь")
        save_path = input()
    links = []
    while True:
        link = input() #https://sun9-51.userapi.com/c10540/u9962023/-6/z_adcdb97a.jpg
        if not link: break
        links.append(link)
    async with aiohttp.ClientSession() as session:
        tasks = [download_image(session, link, save_path) for link in links]
        results = await asyncio.gather(*tasks)
        print(tabulate(results, headers=["Ссылка", "Статус"], tablefmt="grid"))

asyncio.run(get_images())
