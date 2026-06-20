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


if __name__ == "__main__":

    num = 90000000
    
    loop_time = timeit.timeit(lambda: get_gmails_loop(emails), number=num)
    comprehension_time = timeit.timeit(lambda: get_gmails_comprehension(emails), number=num)

    if comprehension_time <= loop_time:
        print("it is better to use a list comprehension")
        print(f"{comprehension_time} vs {loop_time}")
    else:
        print("it is better to use a loop")
        print(f"{loop_time} vs {comprehension_time}")
