input_string = str(input())
N, M = map(int, input_string.split())

matrix = []
for i in range(N):
    vector = list(map(int, input().split()))
    matrix.append(vector)

dp = [[0] * M for _ in range(N)]
dp[0][0] = matrix[0][0]

for j in range(1, M):
    dp[0][j] = dp[0][j - 1] + matrix[0][j]

for i in range(1, N):
    dp[i][0] = dp[i - 1][0] + matrix[i][0]

for i in range(1, N):
    for j in range(1, M):
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j]

print(dp[N - 1][M - 1])
