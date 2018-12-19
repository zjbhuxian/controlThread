#include <iostream>
#include "controlThread.h"

using namespace std;

int main()
{
    ControlThread ctObj;
    char cmd;
    bool bExit = false;
    while(!bExit){
        std::cin >> cmd;
        switch(cmd){
        case '1':
            ctObj.start();
            break;
        case '2':
            ctObj.pause();
            break;
        case '3':
            ctObj.resume();
            break;
        case '0':
            ctObj.stop();
            bExit = true;
            break;
        default:
            ctObj.stop();
            bExit = true;
            break;
        }
    }
}
