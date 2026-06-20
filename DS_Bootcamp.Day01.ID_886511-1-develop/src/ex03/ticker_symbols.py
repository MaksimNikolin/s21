import sys

def ticker_symbols():

    COMPANIES = {
    'Apple'    : 'AAPL',
    'Microsoft': 'MSFT',
    'Netflix'  : 'NFLX',
    'Tesla'    : 'TSLA',
    'Nokia'    : 'NOK'
    }

    STOCKS = {
    'AAPL': 287.73,
    'MSFT': 173.79,
    'NFLX': 416.90,
    'TSLA': 724.88,
    'NOK' : 3.37
    }

    if len(sys.argv) > 2: exit(0)

    ticker = sys.argv[1].upper()
    company = next((k for k, v in COMPANIES.items() if v == ticker), None)
    price = STOCKS.get(ticker)

    if company and price:
        print(f"{company} {price}")
    else:
        print("Unknown ticker")

if __name__ == '__main__':
    ticker_symbols()