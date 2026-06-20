def dict_sorter(list_of_tuples):
    countries = []
    for _ in range(len(list_of_tuples)):
        k, v = list_of_tuples[_]
        countries.append((int(v),k))
    
    for i in range(1, len(countries)):
        for j in range(len(countries)-1):
            if countries[i] > countries[j]:
                countries[i], countries[j] = countries[j], countries[i]

    for i in range(1, len(countries)):
        if countries[i][0] == countries[i-1][0]:
            if countries[i][1] < countries[i-1][1]:
                countries[i], countries[i-1] = countries[i-1], countries[i]
    
    for i in range(len(countries)):
        print(countries[i][1])

list_of_tuples = [
  ('Russia', '25'),
  ('France', '132'),
  ('Germany', '132'),
  ('Spain', '178'),
  ('Italy', '162'),
  ('Portugal', '17'),
  ('Finland', '3'),
  ('Hungary', '2'),
  ('The Netherlands', '28'),
  ('The USA', '610'),
  ('The United Kingdom', '95'),
  ('China', '83'),
  ('Iran', '76'),
  ('Turkey', '65'),
  ('Belgium', '34'),
  ('Canada', '28'),
  ('Switzerland', '26'),
  ('Brazil', '25'),
  ('Austria', '14'),
  ('Israel', '12')
  ]

if __name__ == '__main__':
    dict_sorter(list_of_tuples)
