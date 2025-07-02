#!/bin/bash

GAME_ID="123e4567-e89b-12d3-a456-426614174000"

python3 -m venv daisymal
source daisymal/bin/activate

cd src
pip install --upgrade pip > temp && rm -rf temp 
pip install -r requirements.txt > temp && rm -rf temp 

gunicorn -b 127.0.0.1:5000 main:app > server.log 2>&1 &

SERVER_PID=$!

sleep 2

curl -X POST http://127.0.0.1:5000/game/$GAME_ID \
     -H "Content-Type: application/json" \
     -d "{\"game_id\": \"$GAME_ID\", \"field\": [[0,1,1],[0,2,0],[0,0,2]]}"

kill $SERVER_PID
