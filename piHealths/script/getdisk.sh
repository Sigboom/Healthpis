#!/bin/bash
DISK=(`df -m | grep -v tmp | tail -n +2`) 
NUM=`df -m | grep -v tmp | tail -n +2 | wc -l`
SIZE=0
AVAILABLE=0
for ((i=0; i<NUM; ++i)); do
    DATE=`date -u +"%Y-%m-%d__%H:%M:%S"`
    echo $DATE 1 ${DISK[5+6*$i]} ${DISK[1+6*$i]} ${DISK[3+6*$i]} ${DISK[4+6*$i]}
    SIZE=$SIZE+${DISK[1+6*$i]}
    AVAILABLE=$AVAILABLE+${DISK[3+6*$i]}
done
SIZE=`echo $SIZE | bc`
AVAILABLE=`echo $AVAILABLE | bc`
AVAILABLED=`echo $SIZE $AVAILABLE | awk '{printf("%.0f", $2/$1*100)}'`
echo $DATE 0 disk $SIZE $AVAILABLE $AVAILABLED%
