import csv

def read_and_write():
    with open('ds.csv', 'r', encoding='utf-8') as f:
        reader = csv.reader(f)

        with open('ds.tsv', 'w', encoding='utf-8', newline='') as f:
            writer = csv.writer(f, delimiter='\t')
            for row in reader:
                writer.writerow(row)

if __name__ == '__main__':
    read_and_write()