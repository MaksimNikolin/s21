num_of_steps = 3

report_template = (
    "We have made {num_observations} observations from tossing a coin: "
    "{tails_count} of them were tails and {heads_count} of them were heads. "
    "The probabilities are {tails_fraction:.2f}% and {heads_fraction:.2f}%, respectively. "
    "Our forecast is that in the next {num_steps} observations we will have: "
    "{predicted_tails} tail(s) and {predicted_heads} head(s)."
)

BOT_TOKEN = "7353989248:AAEcKDWWI-xU7fbdX8Zd6UwniOpkmgi8yTE"
CHAT_ID = "153656092"

telegram_webhook_url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage?chat_id={CHAT_ID}"
