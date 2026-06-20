import os
from random import randint
import logging
import requests

logging.basicConfig(
    filename='analytics.log',
    level=logging.INFO,
    format='%(asctime)s %(message)s',
)

class Research():
    def __init__(self, filename):
        self.filename = filename
        logging.info("Initialized Research")

    def file_reader(self, has_header=True):
        logging.info("Reading file")
        with open(self.filename, 'r', encoding='utf-8') as f:
            lines = [line.strip() for line in f if line.strip()]

            if has_header:
                lines = lines[1:]
                if len(lines[0].split(',')) != 2:
                    logging.error("Only 2 columns")
                    raise ValueError("Only 2 columns")

            data = []
            for line in lines:
                if line not in ['0,1', '1,0']:
                    logging.error("Incorrect string")
                    raise ValueError("Incorrect string")

                parts = line.split(',')
                data.append([int(parts[0]), int(parts[1])])
            logging.info("Successfully read file")
            return data

    class Calculations():
        def __init__(self, data):
            self.data = data
            logging.info("Initialized Calculations")

        def counts(self):
            logging.info("Calculating counts")
            c1, c2 = 0, 0 
            for item in self.data:
                if item == [1, 0]:
                    c1 += 1
                elif item == [0, 1]:
                    c2 += 1
            logging.info("Counts successfully calculated")
            return c1, c2

        def fractions(self):
            logging.info("Calculating fractions")
            c1, c2 = self.counts()
            total = c1 + c2
            logging.info("Fractions successfully calculated")
            return (c1 / total * 100, c2 / total * 100)

    def send_message(self, message, webhook_url):
        logging.info("Sending message to Telegram")
        message = {'text': message}
        response = requests.post(webhook_url, json=message)
        if response.status_code == 200:
            logging.info("Successfully sent message to Telegram")
        else:
            logging.error("Failed to send message to Telegram")

class Analytics(Research.Calculations):
    def predict_random(self, steps):
        logging.info(f"Predicting {steps} tails and heads")
        res = []
        for _ in range(steps):
            res.append([1, 0] if randint(0, 1) else [0, 1])
        logging.info("Successfully predicted")
        return res

    def predict_last(self):
        logging.info("Successfully recording tail")
        return self.data[-1]

    def save_file(self, data, filename, extension):
        logging.info("Saving data")
        with open(f"{filename}.{extension}", "w", encoding='utf-8') as f:
            f.write(data)
        logging.info("Data successfully saved")
        