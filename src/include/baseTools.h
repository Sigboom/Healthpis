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
#include <map>
#include <boost/algorithm/string.hpp>

using std::map;
using std::string;
using std::vector;
using boost::trim;

class baseTools {
public:
    baseTools(string confPath);
    //切分字符串
    vector<string> split(const string &str, const string &pattern);
    string getConf(string key);
private:
    string confPath;
    map<string, string> confMap;
};

#endif
