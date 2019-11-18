#########################################################################
# File Name: get_cpu.sh
# Author: daniel
# mail: sigboom@163.com
# Created Time: 五 11/ 1 16:42:05 2019
#########################################################################
#!/bin/bash
TopMessage=`top | head -n 4|tail -n 1`
echo "${TopMessage}"
