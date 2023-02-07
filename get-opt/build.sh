#!/usr/bin/bash
LSRC=lib
LNAME=keyparser
PNAME=package

cd $LSRC
bash build.sh $LNAME $PNAME
if [[ $? == 0 ]]
then
    sudo apt remove $LNAME
    sudo apt install ./$PNAME.deb
fi
cd ..


# PERSONAL CODE
echo "Example assembly ..."
make -C example LNAME=$LNAME >&-
