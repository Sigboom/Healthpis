/*************************************************************************
	> File Name: outPatient.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:14:49 2019
 ************************************************************************/

#include <queue>
#include "doctor.cpp"

using std::queue;
using std::shared_ptr;

class outPatient {
private:
    queue<shared_ptr<doctor> > dq;
    
public:
    outPatient() {}
    ~outPatient(){}

    void toRegister(shared_ptr<patient> pa) {
        dq.push(pa->askDoctor());
        return ;
    }

    void treat() {
        for(auto doc = dq.front(); !dq.empty(); dq.pop()) {
            doc->execute();
        }
        return ;
    }
};

