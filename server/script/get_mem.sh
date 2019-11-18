#########################################################################
# File Name: get_mem.sh
# Author: daniel
# mail: sigboom@163.com
# Created Time: 五 11/ 1 16:01:02 2019
#########################################################################
#!/bin/bash
MemFree=`top | head -n 7 | tail -n 1`
echo " $MemFree"
