import sys
import csv

def letter_starter(email):
    try:
        with open('employees.tsv', 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f, delimiter='\t')
            for row in reader:
                if row['E-mail'].strip().lower() == email.strip().lower():
                    name = row['Name']
                    message = (
                        f"Dear {name}, welcome to our team. "
                        "We are sure that it will be a pleasure to work with you. "
                        "That’s a precondition for the professionals that our company hires."
                    )
                    print(message)
                    return
        print("E-mail not found in employees.tsv")
    except FileNotFoundError: print("File not found")

if __name__ == '__main__':
    if len(sys.argv) != 2: raise ValueError("args")
    letter_starter(sys.argv[1])









