#!/usr/bin/env python3

import httpx
from bs4 import BeautifulSoup
import cProfile
import pstats

def get_field_data(ticker, field):
    url = f"https://www.macrotrends.net/stocks/charts/{ticker}/{ticker.lower()}/revenue"
    headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}

    with httpx.Client(follow_redirects=True) as client:
        response = client.get(url, headers=headers)

        if response.status_code != 200:
            raise Exception(f"URL not found: {url}")

    soup = BeautifulSoup(response.text, 'html.parser')

    try:
        tables = soup.find_all('table')
        for table in tables:
            if 'Annual Revenue' in table.text or 'Total Revenue' in table.text:
                rows = table.find_all('tr')
                revenues = []

                for row in rows[1:]:
                    cells = row.find_all('td')
                    if len(cells) >= 2:
                        year = cells[0].text.strip()
                        revenue = cells[1].text.strip().replace('$', '').replace(',', '')
                        revenues.append(revenue)

                revenues = revenues[:5]

                if not revenues:
                    raise Exception("No revenue data found.")

                return (field, *revenues)
        raise Exception(f"Field '{field}' not found.")

    except Exception as e:
        raise Exception(f"Error parsing data: {e}")

def run_profiler():
    profiler = cProfile.Profile()
    profiler.enable()

    get_field_data("MSFT", "Total Revenue")

    profiler.disable()

    # with open("profiling-http.txt", "w") as f:
    #     stats = pstats.Stats(profiler, stream=f)
    #     stats.sort_stats("tottime")
    #     stats.print_stats()

    # with open("profiling-ncalls.txt", "w") as f:
    #     stats = pstats.Stats(profiler, stream=f)
    #     stats.sort_stats('ncalls')
    #     stats.print_stats()

    with open("pstats-cumulative.txt", "w") as f:
        stats = pstats.Stats(profiler, stream=f)
        stats.sort_stats('cumulative')
        stats.print_stats(5)

if __name__ == "__main__":
    run_profiler()
