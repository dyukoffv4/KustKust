#!/usr/bin/bash

LNAME=keyparser

if [[ ! $(dpkg -l | grep $LNAME) ]]
then
    wget https://github.com/dyukoffv4/KeyParser/releases/download/0.1.1/$LNAME.deb
    sudo apt install ./$LNAME.deb
    rm ./$LNAME.deb
fi

make LNAME=$LNAME
sudo cp bin/count /usr/local/bin/count
