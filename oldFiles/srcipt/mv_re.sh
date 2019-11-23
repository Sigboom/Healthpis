#!/bin/bash

function mv_re() {
    DIR=`ls | awk '{printf("%s\n", $1)}'`
    LEN=`echo $1 | wc -c`
    for d in ${DIR}
    do
        if [ $d != "mv_re.sh" -a ${d:$LEN} != ".sh" -a $d != "add_re.sh" ];then
            if [ "${d:0:$LEN - 1}" == "$1" ];then
                mv $d ${d:$LEN - 1}
            else
                echo $d file_head no $1
            fi
        fi
    done
}


mv_re $1
