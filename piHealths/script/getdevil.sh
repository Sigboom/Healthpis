#!/bin/bash

NUM=`ps -aux | tail -n +2 |wc -l`

declare -a worn
declare -a worn1
declare -a worn2

num=0
num1=0
num2=0

first() {
for i in `seq 1 $NUM` ;do
    temp=(`ps -aux | tail -n $i | head -n 1 | awk '{printf("%s %s %s", $2, $3, $4)}'`)
    if [[ ${temp[1]} > 50 || ${temp[2]} > 50 ]]; then 
       worn[0]=$[${worn[0]} + 1]
       worn[${worn[0]}]=${temp[0]}
        num=$[$num+1]
   fi
done
}

second() {
for ((i=0;i<=num;++i)); do 
    mem=(`ps -aux | grep ${worn[$i]} | awk '{printf("%s %s",$2, $3)}'`)
    if [[ ${mem[1]} > 50 || ${mem[2]} > 50 ]]; then
       worn1[0]=$[${worn1[0]} + 1]
       worn1[${worn1[0]}]=${mem[0]}
        num1=$[$num1+1]
    fi
done
}
    first
    sleep 0.5
    if [[ ${#worn[@]} != 0 ]]; then
        second
    else echo "everything is ok"
    fi

    third() {
    for ((i=0;i<=num1;++i)); do 
        me=(`ps -aux | grep ${worn1[$i]} | awk '{printf("%s %s",$2, $3)}'`)
        if [[ ${me[1]} > 50 || ${me[2]} > 50 ]]; then
            worn2[0]=$[${worn2[0]} + 1]
            worn2[${worn2[0]}]=${me[0]}
            num2=$[$num1+1]
        fi
    done
    }
    sleep 0.5
    if [[ ${#worn1[@]} != 0 ]]; then
        third
        echo woring: danger PID ${worn1[1]} 
    else echo "everything is ok"
    fi
