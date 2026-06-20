def data_types(x):
    res = []
    for i in range(len(x)):
        res.append(type(x[i]).__name__)
    return res

a = [ 4, 'a', 6.5, True, [1,2,3], {1:'a', 2:'b'}, (1,2,3), {1,2,3} ]

if __name__ == '__main__':
      print(data_types(a))