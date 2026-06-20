import sys

def marketing(participants, clients, recipients):
    if len(sys.argv) != 2: raise ValueError("one arg")

    action = sys.argv[1]
    participants_who_not_clients = [p for p in participants if p not in clients]
    clients_who_not_participants = [c for c in clients if c not in participants]
    clients_who_not_seen = [c for c in clients if c not in recipients]

    if action == 'call_center': print(clients_who_not_seen)
    elif action == 'potential_clients': print(participants_who_not_clients)
    elif action == 'loyalty_program': print(clients_who_not_participants)
    else: raise ValueError("unknown arg")

if __name__ == '__main__':
    clients = ['andrew@gmail.com',
            'jessica@gmail.com',
            'ted@mosby.com',
            'john@snow.is',
            'bill_gates@live.com',
            'mark@facebook.com',
            'elon@paypal.com',
            'jessica@gmail.com']
    
    participants = ['walter@heisenberg.com',
                    'vasily@mail.ru',
                    'pinkman@yo.org',
                    'jessica@gmail.com',
                    'elon@paypal.com',
                    'pinkman@yo.org',
                    'mr@robot.gov',
                    'eleven@yahoo.com']

    recipients = ['andrew@gmail.com',
                  'jessica@gmail.com',
                  'john@snow.is']

    marketing(participants, clients, recipients)