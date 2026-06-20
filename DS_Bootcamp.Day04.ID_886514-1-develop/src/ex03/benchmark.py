#!/usr/bin/env python3
 
import timeit
import sys
from functools import reduce

def get_sum_loop(num):
    res = 0
    for i in range(num): res += i ** 2
    return res

def get_sum_reduce(num):
    return reduce(lambda acc, i: acc + i ** 2, range(num), 0)


if __name__ == "__main__":
    
    args = ['loop', 'reduce']
    
    if len(sys.argv) != 4 or sys.argv[1] not in args:
        raise ValueError("Uvays Bakoev")
    num = int(sys.argv[3])

    loop_time = timeit.timeit(lambda: get_sum_loop(num), number=int(sys.argv[2]))
    reduce_time = timeit.timeit(lambda: get_sum_reduce(num), number=int(sys.argv[2]))

    if sys.argv[1] == args[0]: print(loop_time)
    elif sys.argv[1] == args[1]: print(reduce_time)
