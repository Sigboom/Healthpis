/*************************************************************************
	> File Name: debug.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 三  7/18 10:04:53 2018
 ************************************************************************/

#ifndef _DEBUG_H
#define _DEBUG_H

#include <ctype.h>
#include <string.h>

#define DEBUG(C, TYPE) \
    if (strcmp(#TYPE, "int") == 0) printf("%s = %d\n", #C, C); \
    if (strcmp(#TYPE, "char") == 0) printf("%s = %c\n", #C, C); \
    if (strcmp(#TYPE, "string") == 0) printf("%s = %s\n", #C, C)
#endif
