def is_palindrome(num):
    if num < 0: return 0

    new_num, orig_num = 0, num

    while num:
        num, d = divmod(num, 10)
        new_num = new_num*10 + d
    return new_num == orig_num

num = int(input())

if is_palindrome(num):
    print(True)
else:
    print(False)