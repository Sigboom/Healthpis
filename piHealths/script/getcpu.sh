#!/bin/bash
DATE=`date -u +"%Y-%m-%d__%H:%M:%S"`
LOAD=`cat /proc/loadavg | awk '{printf("%s %s %s", $1, $2, $3)}'`
SUM1=`head -1 /proc/stat | tr [a-z] 0 | tr -s ' ' '+' | bc`
FREE1=`head -1 /proc/stat | awk '{printf("%s", $5)}'`
sleep 0.5
SUM2=`head -1 /proc/stat | tr [a-z] 0 | tr -s ' ' '+' | bc`
FREE2=`head -1 /proc/stat | awk '{printf("%s", $5)}'`
LV=`echo $SUM1 $FREE1 $SUM2 $FREE2 | awk '{printf("%.2f", (1-($4-$2)/($3-$1))*100)}'`
TEMPRUTURE=`cat /sys/class/thermal/thermal_zone0/temp | cut -c -2` 
if [ $TEMPRUTURE -lt 50 ];then
    STATE=normal;
elif [ $TEMPRUTURE -le 70 ];then
    STATE=note;
else
    STATE=warning;
fi
echo $DATE $LOAD $LV% $TEMPRUTURE°C $STATE
