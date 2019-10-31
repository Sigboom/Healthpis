/*************************************************************************
	> File Name: baseTools.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 10/22 23:42:20 2019
 ************************************************************************/

#ifndef _BASETOOLS_H
#define _BASETOOLS_H

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class baseTools {
public:
    baseTools(std::string confPath);
    //切分字符串
    std::vector<std::string> split(const std::string &str, const std::string &pattern);

    std::string getConf(std::string key);
private:
    std::string confPath;
};

#endif
