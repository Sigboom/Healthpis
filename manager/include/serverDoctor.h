/*************************************************************************
	> File Name: serverDoctor.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 六 11/23 15:51:46 2019
 ************************************************************************/

#ifndef _SERVERDOCTOR_H
#define _SERVERDOCTOR_H

#include "../../sigToolkit/include/sigToolkit.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

class fileDoctor: public doctor {
private:
    shared_ptr<mediCentre> mc;
    string logPath;

public:
    fileDoctor(shared_ptr<mediCentre> mc);    
    void execute(string sym);

private:
    void mkdirPath(string path);

};

class serverDoctor: public doctor {
private:
    shared_ptr<mediCentre> mc;

public:
    serverDoctor(shared_ptr<mediCentre> mc);
    void execute(string sym);

private:
    void s_connect(int id);
    void connect(string station);
};

#endif
