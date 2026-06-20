import sys
from analytics import Research, Analytics
import config
import logging

def main():
    if len(sys.argv) != 2: raise ValueError("args_count")

    path = sys.argv[1]
    research = Research(path)
    try:
        data = research.file_reader()

        calculations = Research.Calculations(data)
        c1, c2 = calculations.counts()
        frac = calculations.fractions()

        analytics = Analytics(data)
        predictions = analytics.predict_random(config.num_of_steps)

        report_text = config.report_template.format(
            num_observations=len(data),
            tails_count = c2,
            heads_count = c1,
            tails_fraction = frac[0],
            heads_fraction = frac[1],
            num_steps = config.num_of_steps,
            predicted_tails = sum(1 for p in predictions if p == [0, 1]),
            predicted_heads = sum(1 for p in predictions if p == [1, 0]),
        )

        analytics.save_file(report_text, "report", "txt")
        research.send_message("The report successfully created", config.telegram_webhook_url)

    except Exception as e:
        logging.error(f"An error occurred: {e}")
        research.send_message("The report hasn't been created due to an error", config.telegram_webhook_url)

if __name__ == "__main__":
    main()
