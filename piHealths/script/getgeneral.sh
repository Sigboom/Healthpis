#!/bin/bash
DATE=`date -u +"%Y-%m-%d__%H:%M:%S"`
HOSTNAME=`hostname`
COREOS=`uname -o`
COREV=`uname -r`
UPTIME=`uptime -p | tr " " "_"`
AVLOAD=(`cat /proc/loadavg`)
DISK=(`df -m | grep -v tmp | tail -n +2`) 
NUM=`df -m | grep -v tmp | tail -n +2 | wc -l`
SIZE=0
USE=0
for ((i=0; i<NUM; ++i)); do
    SIZE=$SIZE+${DISK[1+6*$i]}
    USE=$USE+${DISK[2+6*$i]}
done
SIZE=`echo $SIZE | bc`
USE=`echo $USE | bc`
DISKUSED=`echo $SIZE $USE | awk '{printf("%.0f", $2/$1*100)}'`
MEM=(`free -m | head -n 2 | tail -1 | awk '{printf("%d %d", $2, $3/$2*100)}'`)
MEMUSED=${MEM[1]}
TEMPRUTURE=`cat /sys/class/thermal/thermal_zone0/temp | cut -c -2` 

if [[ $DISKUSED -lt 80 ]];then
    DISKFLAG=normal
elif [[ $DISKUSED -lt 90 ]];then
    DISKFLAG=note
else
    DISKFLAG=warning
fi

if [[ $MEMUSED -lt 70 ]];then
    MEMFLAG=normal
elif [[ $MEMUSED -lt 80 ]];then
    MEMFLAG=note
else
    MEMFLAG=warning
fi

if [[ $TEMPRUTURE -lt 70 ]];then
    TEMPRUTUREFLAG=normal
elif [[ $TEMPRUTURE -lt 80 ]];then
    TEMPRUTUREFLAG=note
else
    TEMPRUTUREFLAG=warning
fi

echo $DATE $HOSTNAME $COREOS $COREV $UPTIME ${AVLOAD[0]} ${AVLOAD[1]} ${AVLOAD[2]} $SIZE $DISKUSED% $MEM% $TEMPRUTURE°C $DISKFLAG $MEMFLAG $TEMPRUTUREFLAG
