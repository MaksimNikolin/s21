#!/usr/bin/env python3

import sys
import requests
from bs4 import BeautifulSoup
import time

def get_field_data(ticker, field):

    url = f"https://www.macrotrends.net/stocks/charts/{ticker}/{ticker.lower()}/revenue"
    headers = {'User-Agent': 'Mozilla/5.0'}
    response = requests.get(url, headers=headers)

    if response.status_code != 200:
        raise Exception(f"URL not found: {url}")

    soup = BeautifulSoup(response.text, 'html.parser')
    time.sleep(5)

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

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 financial.py <ticker_symbol> <field_name>")
        sys.exit(1)

    ticker, field = sys.argv[1], sys.argv[2]

    try:
        result = get_field_data(ticker, field)
        print(result)

    except Exception as e:
        print(e)
        sys.exit(1)
