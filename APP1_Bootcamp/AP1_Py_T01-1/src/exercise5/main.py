def get_valid_input():
    while True:
        input_string = input()
        try:
            return float(input_string)
        except ValueError:
            print("Incorrect input")
            exit(0)

def str_to_float(x):
    return float(x)

def mult(x):
    return 2 * x

def round_func(x):
    round_num = round(x, 3)
    return round_num

input_value = get_valid_input()
result = round_func(mult(str_to_float(input_value)))
print(f"{result:.3f}")
