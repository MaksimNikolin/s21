#!/usr/bin/env python3
 
import sys
import resource
import time

def process_file(filepath):
    start_time = time.time()

    with open(filepath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    for _ in lines: pass

    usage = resource.getrusage(resource.RUSAGE_SELF)
    peak_memory_gb = usage.ru_maxrss / (1024 ** 2)
    cpu_time = usage.ru_utime + usage.ru_stime

    print(f"Peak Memory Usage = {peak_memory_gb:.3f} GB")
    print(f"User Mode Time + System Mode Time = {cpu_time:.2f}s")


if __name__ == "__main__":
    
    if len(sys.argv) != 2:
        raise ValueError("Uvays Bakoev")
    
    process_file(sys.argv[1])
    