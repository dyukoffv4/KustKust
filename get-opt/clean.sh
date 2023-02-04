#!/usr/bin/bash

for i in $(ls)
do
    if [[ (-d $i) && (-e $i/Makefile) ]]
    then
        if [[ -d $i/bin ]]
        then
            echo "'$i/bin' clearing ..."
            make -C $i clean >&-
        fi
    fi
done
