#!/bin/bash
#Using for gathring information of Mem

function Usage() {
    echo "Usage: $0 DyAver"
}

#if [[ $# -lt 1 ]]; then 
#    Usage
#    exit
#fi

#DyAver=$1
DATE=`date +"%Y-%m-%d__%H:%M:%S"`
MEMVALUE=(`free -m | tail -n +2 | head -n -1 | awk '{printf("%s %s %.2f",$2,$3,$3*100/$2)}'`)
#NowAver=`echo "scale=2;0.8*${MEMVALUE[2]}+0.2*${DyAver}"|bc`
echo $DATE total = ${MEMVALUE[0]} use = ${MEMVALUE[1]} usuaver = ${MEMVALUE[2]}% #dynamic = $NowAver%
