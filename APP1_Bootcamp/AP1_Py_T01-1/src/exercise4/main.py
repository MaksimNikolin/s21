def get_valid_input():
    while True:
        try:
            numRows = int(input())
            if numRows > 0: return numRows
            else: print("Incorrect input")
        except ValueError:
            print("Incorrect input")

def pascal_triangle(numRows):
    dp = [[1], [1, 1]]
    if numRows < 3: return dp[:numRows]

    for i in range(numRows-2): 
        next_row = [1]
        for j in range(1, len(dp[-1])) :
            next_row.append(dp[-1][j] + dp[-1][j-1])

        next_row += [1]
        dp.append(next_row)

    return dp

numRows = get_valid_input()
print(pascal_triangle(numRows))
