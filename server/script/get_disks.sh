#########################################################################
# File Name: get_disks.sh
# Author: daniel
# mail: sigboom@163.com
# Created Time: 五 11/ 1 16:48:43 2019
#########################################################################
#!/bin/bash
disks=`top | head -n 10 |tail -n -1`
echo "${disks}"
