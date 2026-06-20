#!/usr/bin/env python3
 
import timeit
import sys

emails = ['john@gmail.com',
          'james@gmail.com',
          'alice@yahoo.com', 
          'anna@live.com',
          'philipp@gmail.com'
          ]

emails *= 5

def get_gmails_loop(emails):
    res = []
    for email in emails:
        if '@gmail.com' in email:
            res.append(email)
    return res

def get_gmails_comprehension(emails):
    return [email for email in emails if '@gmail.com' in email]

def get_gmails_map(emails):
    return list(map(lambda email: email if '@gmail.com' in email else None, emails))

def get_gmails_filter(emails):
    return list(filter(lambda email: email if '@gmail.com' in email else None, emails))

if __name__ == "__main__":
    
    args = ['loop', 'list_comprehension', 'map', 'filter']
    if len(sys.argv) != 3 or sys.argv[1] not in args:
        raise ValueError("Uvays Bakoev")

    loop_time = timeit.timeit(lambda: get_gmails_loop(emails), number=int(sys.argv[2]))
    comprehension_time = timeit.timeit(lambda: get_gmails_comprehension(emails), number=int(sys.argv[2]))
    map_time = timeit.timeit(lambda: get_gmails_map(emails), number=int(sys.argv[2]))
    filter_time = timeit.timeit(lambda: get_gmails_filter(emails), number=int(sys.argv[2]))

    if sys.argv[1] == args[0]:
        print(loop_time)
    elif sys.argv[1] == args[1]:
        print(comprehension_time)
    elif sys.argv[1] == args[2]:
        print(map_time)
    elif sys.argv[1] == args[3]:
        print(filter_time)
