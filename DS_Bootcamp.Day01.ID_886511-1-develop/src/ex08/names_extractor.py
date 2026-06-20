import sys

def names_extractor(path):
    with open(path, 'r', encoding='utf-8') as f:
        emails = [line.strip() for line in f if line.strip()]

    output_lines = ["Name\tSurname\tE-mail"]
    
    for email in emails:
        if '@' not in email or '.' not in email.split('@')[0]: continue
        name_part = email.split('@')[0]
        name, surname = name_part.split('.')
        name = name.capitalize()
        surname = surname.capitalize()
        output_lines.append(f"{name}\t{surname}\t{email}")

    with open('employees.tsv', 'w', encoding='utf-8') as f:
        f.write('\n'.join(output_lines))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise ValueError("Usage: python3 script.py <path_to_email_file>")
    names_extractor(sys.argv[1])














