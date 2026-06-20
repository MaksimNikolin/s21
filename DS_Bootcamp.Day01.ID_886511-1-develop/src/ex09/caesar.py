import sys

def caesar():
    text = sys.argv[2]
    shift = int(sys.argv[3])
    res = ''

    for char in text:
        if 'a' <= char <= 'z':
            if sys.argv[1] == 'encode':
                shifted = (ord(char) - ord('a') + shift) % 26 + ord('a')
            elif sys.argv[1] == 'decode':
                shifted = (ord(char) - ord('a') - shift) % 26 + ord('a')
            else:
                raise ValueError("Unknown arg")
            res += chr(shifted)
        else:
            res += char
    print(res)

if __name__ == "__main__":
    if len(sys.argv) != 4: raise ValueError("args_count")
    caesar()