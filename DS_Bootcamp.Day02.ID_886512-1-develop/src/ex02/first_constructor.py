import sys
import os

class Research():
    def __init__(self, filename):
        self.filename = filename

    def file_reader(self):
        with open(self.filename, 'r', encoding='utf-8') as f:
            lines = [line.strip() for line in f if line.strip()]
            
            if len(lines[0].split(',')) != 2:
                raise ValueError("only 2 columns")
            
            for line in lines[1:]:
                if line not in ['0,1', '1,0']:
                    raise ValueError("incorrect string")

            return lines

if __name__ == "__main__":
    if len(sys.argv) != 2: raise ValueError("args_count")
    
    path = sys.argv[1]
    reader = Research(path)
    for line in reader.file_reader():
        print(line)
