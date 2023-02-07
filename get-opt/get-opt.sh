#!/usr/bin/bash
if [[ $# == 0 ]]; then exit 1; fi

if [[ $1 == "build" ]]; then F_BUILD=true
elif [[ $1 == "clean" ]]; then F_CLEAN=true
elif [[ $1 == "prune" ]]; then F_PRUNE=true; F_CLEAN=true
else exit 1; fi

LSRC=lib
LNAME=keyparser
PNAME=package

if [ $F_BUILD ]
then
    cd $LSRC
    bash build.sh $LNAME $PNAME
    if [[ $? == 0 ]]
    then
        if [[ $(dpkg -l | grep $LNAME) ]]; then sudo apt reinstall ./$PNAME.deb
        else sudo apt install ./$PNAME.deb; fi
    fi
    cd ..
elif [ $F_CLEAN ]
then
    cd $LSRC
    bash clean.sh
    if [[ $F_PRUNE && $(dpkg -l | grep $LNAME) ]]; then sudo apt remove $LNAME; fi
    cd ..
fi


# PERSONAL CODE
if [ $F_BUILD ]; then echo "Example assembly ..."; make -C example LNAME=$LNAME >&-
else echo "Example clean ..."; make -C example LNAME=$LNAME clean >&-; fi
