import sys

def all_stocks():

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

    line = sys.argv[1]
    parts = line.split(',')
    for i in range(len(parts)):
        if parts[i] == ' ' or parts[i] == '': exit(0)
    else :
        for i in range(len(parts)): 
            if parts[i].replace(' ', '').capitalize() in COMPANIES.keys():
                company = parts[i].replace(' ', '').capitalize()
                ticker = COMPANIES.get(company)
                price = STOCKS.get(ticker)
                print(f"{company} stock price is {price}")
            elif parts[i].replace(' ', '').upper() in COMPANIES.values():
                ticker = parts[i].replace(' ', '').upper()
                company = next((k for k, v in COMPANIES.items() if v == ticker), None)
                print(f"{ticker} is a ticker symbol for {company}")
            else:
                name = parts[i].replace(' ', '')
                print(f"{name} is an unknown company or an unknown ticker symbol")

if __name__ == '__main__':
    all_stocks()