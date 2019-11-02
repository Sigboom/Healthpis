/*************************************************************************
	> File Name: test.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五 11/ 1 15:59:46 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
using namespace std;
using boost::trim;

int main() {
    string str = " 124   key  134  = 124value134 ";
    size_t pos = str.find("=");
    string key = str.substr(0, pos);
    cout << "key:" << key << endl;
    trim(key);
    cout << "key:" << key << endl;
    return 0;
}
