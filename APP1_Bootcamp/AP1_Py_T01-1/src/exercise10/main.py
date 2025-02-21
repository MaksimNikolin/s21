try:
    N, required_time = map(int, input().split())
    if N <= 0 or required_time <= 0:
        raise ValueError("Input error")

    machines = []
    for _ in range(N):
        year, cost, work_time = map(int, input().split())
        if year <= 0 or cost <= 0 or work_time <= 0:
            raise ValueError("Input error")
        machines.append((year, cost, work_time))
        
    from collections import defaultdict
    machines_by_year = defaultdict(list)
        
    for year, cost, work_time in machines:
        machines_by_year[year].append((cost, work_time))
        
    min_cost = float('inf')

    for year, machine_list in machines_by_year.items():
        for i in range(len(machine_list)):
            for j in range(i + 1, len(machine_list)):
                cost1, time1 = machine_list[i]
                cost2, time2 = machine_list[j]
                if time1 + time2 == required_time:
                    min_cost = min(min_cost, cost1 + cost2)

    if min_cost == float('inf'):
        print("Error")
    else:
        print(min_cost)
    
except Exception as e:
    print("Error")