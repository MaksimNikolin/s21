import numpy as np
import math

with open('input.txt', 'r', encoding='UTF-8') as file:
    lines = file.readlines()

matrix = [list(map(int, line.split())) for line in lines]
matrix = np.array(matrix)
rows, cols = matrix.shape

def dfs(matrix, i, j, visited):
    stack = [(i, j)]
    visited[i][j] = True
    component = []

    while stack:
        x, y = stack.pop()
        component.append((x, y))

        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and not visited[nx][ny] and matrix[nx][ny] == 1:
                visited[nx][ny] = True
                stack.append((nx, ny))

    return component

def is_square_number(n):
    sqrt_n = math.sqrt(n)
    return sqrt_n.is_integer()

def counting_squares_and_circles(matrix, rows, cols):
    visited = np.zeros_like(matrix, dtype=bool)
    square_count, circle_count = 0, 0

    for i in range(rows):
        for j in range(cols):
            if matrix[i, j] == 1 and not visited[i, j]:
                component = dfs(matrix, i, j, visited)
                if is_square_number(len(component)): square_count += 1
                else: circle_count += 1

    return square_count, circle_count

square_count, circle_count = counting_squares_and_circles(matrix, rows, cols)
print(square_count, circle_count)
