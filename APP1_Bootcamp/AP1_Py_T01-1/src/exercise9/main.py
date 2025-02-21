res = 0

string = input()
cnt_of_poly, der = map(float, string.split())
list_of_poly = []

for i in range(int(cnt_of_poly)+1):
    num = input()
    list_of_poly.append(float(num))

for i in range(len(list_of_poly)):
    list_of_poly[i] *= ((len(list_of_poly))-i-1) * der**((len(list_of_poly))-i-2)

for i in range(len(list_of_poly)):
    res += list_of_poly[i]

print(f"{res:.3f}")