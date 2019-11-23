/*************************************************************************
	> File Name: baseTools.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 10/22 23:17:13 2019
 ************************************************************************/

#include "../include/baseTools.h" 

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::ifstream;
using std::size_t;

using boost::trim;

baseTools::baseTools(string confPath) : confPath(confPath) {
#ifdef SIG_TEST
    cout << "baseTools catch confPath: " << confPath << endl;
#endif
    ifstream valueStream(confPath);
    if (valueStream.is_open()) {
        string temp, key, value;
        size_t pos = 0;
        while (!valueStream.eof()) {
            valueStream >> temp;
            trim(temp);
            if(temp.length() == 0) continue;
            if ((pos = temp.find("=")) != string::npos) {
                key = temp.substr(0, pos);
                value = temp.substr(pos + 1);
                trim(key);
                trim(value);
                if (*(value.begin()) == '[') {
                    if (*(value.end() - 1) != ']') {
                        while (!valueStream.eof()) {
                            valueStream >> temp;
                            trim(temp);
                            value += temp;
                            if (*(temp.end() - 1) == ']' ||
                                (temp.length() > 1 &&
                                 *(temp.end() - 1) == ';' &&
                                 *(temp.end() - 2) == ']')) break;
                        }
                    }
                    value = value.substr(1, value.size() - 2);
                }
                confMap.insert(pair<string, string>(key, value));
                key.clear();
                value.clear();
                temp.clear();
            } else {
                //cout << "error: " << temp << endl;
                throw -2;
            }
        }
        valueStream.close();
    } else throw -1;
#ifdef SIG_INIT
    cout << "confMap read over!" << endl;
    for (auto it = confMap.begin(); it != confMap.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
#endif
}

vector<string> baseTools::split(const string &str,const string &pattern) {
    vector<string> resVec;
    if (str.empty()) return resVec;
    //方便截取最后一段数据
    string strs = str + pattern;
    size_t pos = strs.find(pattern);
    while (pos != string::npos) {
        string x = strs.substr(0, pos);
        resVec.push_back(x);
        strs = strs.substr(pos + 1);
        pos = strs.find(pattern);
    }
    return resVec;
}

string baseTools::getConf(string key) {
    map<string, string>::iterator it = confMap.find(key);
    if (it != confMap.end()) {
        //cout << "key: " << key << " => " << confMap.find(key)->second << endl;
        return it->second;
    } else throw -3;
    return "";
}
