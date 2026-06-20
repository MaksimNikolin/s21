#!/usr/bin/env python3
 
import timeit
import random
from collections import Counter

def count_numbers_manual(nums):
    counts = {}
    for num in nums:
        if num in counts: counts[num] += 1
        else: counts[num] = 1
    return counts

def top_10_manual(nums):
    counts = count_numbers_manual(nums)
    return dict(sorted(counts.items(), key=lambda item: item[1], reverse=True)[:10])

def count_numbers_counter(nums):
    return dict(Counter(nums))

def top_10_counter(nums):
    return dict(Counter(nums).most_common(10))

if __name__ == "__main__":
    
    nums = [random.randint(0, 100) for _ in range(1000000)]
    
    manual_count_time = timeit.timeit(lambda: count_numbers_manual(nums), number=1)
    counter_count_time = timeit.timeit(lambda: count_numbers_counter(nums), number=1)

    manual_top_time = timeit.timeit(lambda: top_10_manual(nums), number=1)
    counter_top_time = timeit.timeit(lambda: top_10_counter(nums), number=1)

    print(f"my function: {manual_count_time:.7f}")
    print(f"Counter: {counter_count_time:.7f}")
    print(f"my top: {manual_top_time:.7f}")
    print(f"Counter's top: {counter_top_time:.7f}")

