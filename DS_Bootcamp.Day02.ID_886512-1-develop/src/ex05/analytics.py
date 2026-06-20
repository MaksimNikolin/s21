import os
from random import randint

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
        def __init__(self, data):
            self.data = data

        def counts(self):
            c1, c2 = 0, 0 
            for item in self.data:
                if item == [1, 0]:
                    c1 += 1
                elif item == [0, 1]:
                    c2 += 1
            return c1, c2

        def fractions(self):
            c1, c2 = self.counts()
            total = c1 + c2
            return (c1 / total * 100, c2 / total * 100)

class Analytics(Research.Calculations):
    def predict_random(self, steps):
        res = []
        for _ in range(steps):
            res.append([1, 0] if randint(0, 1) else [0, 1])
        return res

    def predict_last(self):
        return self.data[-1]

    def save_file(self, data, filename, extension):
        with open(f"{filename}.{extension}", "w", encoding='utf-8') as f:
            f.write(data)
