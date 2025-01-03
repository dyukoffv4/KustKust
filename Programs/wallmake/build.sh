#!/usr/bin/bash

if [[ ! $(dpkg -l | grep keyparser) ]]
then
    wget https://github.com/dyukoffv4/KeyParser/releases/download/1.1.0/keyparser.deb
    sudo apt install ./keyparser.deb
    rm ./keyparser.deb
fi

mkdir -p bin
g++ code/xml/tag.cpp code/main.cpp -lkeyparser -o bin/wallmake
