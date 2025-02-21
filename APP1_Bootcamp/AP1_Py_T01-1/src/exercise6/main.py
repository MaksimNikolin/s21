import json

def get_valid_input():
    while True:
        try:
            with open('input.txt', 'r', encoding='UTF-8') as file:
                data = file.read()

            try:
                json_data = json.loads(data)
            except json.JSONDecodeError:
                print("Incorrect input"), exit(0)

            if "list1" not in json_data or "list2" not in json_data:
                print("Incorrect input"), exit(0)

            list1, list2 = json_data["list1"], json_data["list2"]

            return list1, list2

        except FileNotFoundError:
            print("File not found"), exit(0)

        except Exception as e:
            print(f"Error: {e}"), exit(0)

list1, list2 = get_valid_input()

list0 = list1 + list2
res = {"list0": list0}
sorted_list = sorted(res["list0"], key=lambda x: x['year'])
print({"list0": sorted_list})
