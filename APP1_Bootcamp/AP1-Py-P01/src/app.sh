#!/bin/bash

loading_animation() {
    local spin='-\|/'
    local i=0
    echo -n "LOADING... "
    
    while :; do
        printf "\rLOADING... ${spin:i++%${#spin}:1}"
        sleep 0.1
    done
}

loading_animation &
animation_pid=$!

rm -rf myenv
python3 -m venv myenv
source myenv/bin/activate

pip install pygame loguru --quiet &> /dev/null &

pid=$!
wait $pid
kill $animation_pid

python3 main.py