import sys

def stock_prices():

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

    company = sys.argv[1].capitalize()
    ticker = COMPANIES.get(company)

    if ticker:
        price = STOCKS.get(ticker)
        print(f"{price}")
    else:
        print("Unknown company")

if __name__ == '__main__':
    stock_prices()