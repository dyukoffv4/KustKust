#!/usr/bin/bash
DLIB=lib
ALIB=$(pwd)/$DLIB/bin

# LIBRARY ASSEMBLY
echo "Library assembly ..."
if [[ ! -d $DLIB/bin ]]
then mkdir $DLIB/bin
fi
make -C $DLIB >&-

if [[ ! $(grep -E "LD_LIBRARY_PATH=$ALIB" ~/.bashrc) ]]
then
    echo "Path creating code add (~/.bashrc)...\n"
    if [[ $(echo $LD_LIBRARY_PATH | grep -E "$ALIB") ]]
    then echo "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}" >> ~/.bashrc
    else echo "LD_LIBRARY_PATH=$ALIB:${LD_LIBRARY_PATH}" >> ~/.bashrc
    fi
fi

# PERSONAL CODE
for i in $(ls)
do
    if [[ (-d $i) && (-e $i/Makefile) && ($i != $DLIB) ]]
    then
        echo "Diretory code '$i' assembly ..."
        if [[ ! -d $i/bin ]]
        then mkdir $i/bin
        fi
        make -C $i LIB=$ALIB >&-
    fi
done
