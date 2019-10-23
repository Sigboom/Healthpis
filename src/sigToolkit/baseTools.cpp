/*************************************************************************
	> File Name: baseTools.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 10/22 23:17:13 2019
 ************************************************************************/

#include "../include/baseTools.h" 

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;

baseTools::baseTools(string confPath) : confPath(confPath) {}

vector<string> baseTools::split(const string &str,const string &pattern) {
    vector<string> resVec;
    if (str.empty()) return resVec;
    //方便截取最后一段数据
    string strs = str + pattern;
    size_t pos = strs.find(pattern), size = strs.size();
    while (pos != string::npos) {
        string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1, size);
        pos = strs.find(pattern);
    }
    return resVec;
}

string baseTools::getConf(string key) {
    ifstream valueStream(confPath);
    string temp, res;
    if (valueStream.is_open()) {
        //cout << "valueStream is open!" << endl;
        while (!valueStream.eof()) {
            valueStream >> temp;
            int n = key.length() + 1;
            //找到对应key
            if (temp.find(key + "=") != string::npos) {
                //cout << "catch key: " << key << endl;
                //消除空格
                while (temp[n] == ' ') n++;
                //cout << "check temp: " << temp << endl;
                //数组判定
                if (temp[n] == '[') {
                    if (*(temp.end() - 1) == ']') res = temp.substr(n + 1, temp.length() - 1);
                    else if(*(temp.end() - 1) == ';' && *(temp.end() - 2) == ']')
                        res = temp.substr(n + 1, temp.length() - 2);
                    else {
                        res = temp.substr(n + 1);
                        while (!valueStream.eof()) {
                            valueStream >> temp;
                            //cout << "check temp:" << temp << endl;
                            if (*(temp.end() - 1) == ']') {
                                res += temp.substr(0, temp.length() - 1);
                                return res;
                            } else if(*(temp.end() - 1) == ';' && *(temp.end() - 2) == ']') {
                                res += temp.substr(0, temp.length() - 2);
                                return res;
                            } else res += temp;
                            //cout << "check res: " << res << endl;
                        }
                    }
                } else res = temp.substr(n);
                //cout << "check return res: " << res << endl;
                return res;
            }
        }
    } else {
        cout << "Error opening file" << endl;
        exit(1);
    }
    return res;
}
