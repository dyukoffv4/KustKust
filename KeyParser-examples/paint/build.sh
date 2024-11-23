#!/usr/bin/bash

if [[ ! $(dpkg -l | grep keyparser) ]]
then
    wget https://github.com/dyukoffv4/KeyParser/releases/download/1.0.1/keyparser.deb
    sudo apt install ./keyparser.deb
    rm ./keyparser.deb
fi

mkdir -p bin
g++ src/paint.cpp src/main.cpp -lkeyparser -o bin/paint
