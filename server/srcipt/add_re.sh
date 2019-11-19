#!/bin/bash

function add_re() {
    DIR=`ls | awk '{printf("%s\n", $1)}'`
    for d in ${DIR}
    do
        if [ $d != "add_re.sh" -a $d != "mv_re.sh" ];then
            mv $d $1$d 
        fi
    done
}

if [ -n $1 ];then
    add_re $1
else 
    echo please input "<file_head>"
fi
