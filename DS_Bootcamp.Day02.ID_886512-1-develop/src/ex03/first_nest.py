import sys
import os

class Research():
    def __init__(self, filename):
        self.filename = filename

    def file_reader(self, has_header=True):
        with open(self.filename, 'r', encoding='utf-8') as f:
            lines = [line.strip() for line in f if line.strip()]

            if has_header:
                lines = lines[1:]
                if len(lines[0].split(',')) != 2:
                    raise ValueError("only 2 columns")
                
            data = []
            for line in lines:
                if line not in ['0,1', '1,0']:
                    raise ValueError("incorrect string")

                parts = line.split(',')
                data.append([int(parts[0]), int(parts[1])])
            return data

    class Calculations():
        @staticmethod
        def counts(data):
            c1, c2 = 0, 0 
            for item in data:
                if item == [1, 0]: c1 += 1
                elif item == [0, 1]: c2 += 1
            return (f"{c1} {c2}")

        @staticmethod
        def fractions(data):
            c1, c2 = 0, 0 
            for item in data:
                if item == [1, 0]: c1 += 1
                elif item == [0, 1]: c2 += 1
            return (f"{c1/(c1+c2)*100} {c2/(c1+c2)*100}")

if __name__ == "__main__":
    if len(sys.argv) != 2: raise ValueError("args_count") 

    path = sys.argv[1]
    reader = Research(path)
    
    data = reader.file_reader()
    print(data)

    count = reader.Calculations.counts(data)
    print(count)

    frac = reader.Calculations.fractions(data)
    print(frac)