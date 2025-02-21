nums = int(input())
nums_massive = []

for i in range(nums):
    num = int(input())
    nums_massive.append(num)

print(len(set(nums_massive)))
