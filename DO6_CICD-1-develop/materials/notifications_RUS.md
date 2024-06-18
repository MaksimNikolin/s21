## GitLab CI & Telegram

- Создать телеграмм бота.
- Отправить боту сообщение, чтобы он настроился для работы с пользователем (тобой).
- Сохранить нужные значения в **GitLab**:
  - *Settings* нужного репозитория;
  - Пункт **CI/CD**;
  - *Переменные*;
  - Сохранить в переменную *TELEGRAM_BOT_TOKEN* token созданного бота;
  - В *TELEGRAM_USER_ID* сохранить ID пользователя, которому будут отправляться уведомления.

Для удобной отправки уведомлений имеет смысл создать bash-скрипт, в котором будет обращение к **API Telegram** и отправка сообщения нужному пользователю через созданного бота. Вот пример подобного скрипта:

```bash
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
```

P.S. В качестве первого параметра для этого скрипта должен передаваться статус деплоя.

