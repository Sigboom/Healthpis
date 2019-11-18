#########################################################################
# File Name: get_net.sh
# Author: daniel
# mail: sigboom@163.com
# Created Time: 五 11/ 1 16:58:18 2019
#########################################################################
#!/bin/bash
Net=`ifconfig | head -n 14 | tail -n 1`
echo "${Net}"
