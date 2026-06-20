#!/usr/bin/env python3

import timeit

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

if __name__ == "__main__":

    num = 90000000

    loop_time = timeit.timeit(lambda: get_gmails_loop(emails), number=num)
    comprehension_time = timeit.timeit(lambda: get_gmails_comprehension(emails), number=num)
    map_time = timeit.timeit(lambda: get_gmails_map(emails), number=num)

    if map_time <= loop_time and map_time <= comprehension_time:
        print("it is better to use a map")
        if comprehension_time <= loop_time:
            print(f"{map_time} vs {comprehension_time} vs {loop_time}")
        else:
            print(f"{map_time} vs {loop_time} vs {comprehension_time}")

    elif comprehension_time <= map_time and comprehension_time <= loop_time:
        print("it is better to use a list comprehension")
        if loop_time <= map_time:
            print(f"{comprehension_time} vs {loop_time} vs {map_time}")
        else:
            print(f"{comprehension_time} vs {map_time} vs {loop_time}")

    else:
        print("it is better to use a loop")
        if comprehension_time <= map_time:
            print(f"{loop_time} vs {comprehension_time} vs {map_time}")
        else:
            print(f"{loop_time} vs {map_time} vs {comprehension_time}")