#!/usr/bin/bash

SRC_COM=src/components
NAME=main.out

if [[ ! $(dpkg -l | grep libsfml-dev) ]]; then
    sudo apt-get install libsfml-dev
fi

for i in $(echo "$(ls src/components)"); do
    if [[ -d $SRC_COM/$i ]]; then
        make part HPP="$SRC_COM/$i/$i.hpp" CPP="$SRC_COM/$i/$i.cpp" NAME=$i
    fi
done

for i in $(echo "$(ls out)"); do FROM="$FROM out/$i"; done

make FROM="$FROM" NAME=$NAME
