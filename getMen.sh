#!/bin/bash
#create by Daniel in 2018.7.18

DATE=`date +"%Y-%m-%d__%H:%M:%S"`
MEMVALUE=`top -l 1 | grep PhysMem`
echo $DATE ${MEMVALUE}
