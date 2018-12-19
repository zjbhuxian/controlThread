#include <iostream>
#include "controlThread.h"

using namespace std;

static bool watch_event_handler( fswatcher_event_handler* handler, fswatcher_event_type evtype, const char* src, const char* dst )
{
	(void)handler; (void)dst;

	switch( evtype )
	{
		case FSWATCHER_EVENT_CREATE: printf("item create %s!\n", src); break;
		case FSWATCHER_EVENT_REMOVE: printf("item remove %s!\n", src); break;
		case FSWATCHER_EVENT_MODIFY: printf("item modify %s!\n", src); break;
		case FSWATCHER_EVENT_MOVE:   printf("item moved %s -> %s!\n", src, dst); break;
		default:
			printf("unhandled event!\n");
	}
	return true;
}

int main()
{
    fswatcher_t watcher = fswatcher_create( FSWATCHER_CREATE_DEFAULT, FSWATCHER_EVENT_ALL, "E:\\", 0x0 );
	fswatcher_t watcher2 = fswatcher_create( FSWATCHER_CREATE_DEFAULT, FSWATCHER_EVENT_ALL, "D:\\", 0x0 );
	fswatcher_event_handler handler = { watch_event_handler };

    ControlThread ctObj2("ctObj2");
//    ctObj2.setPath("ctObj2");
    ctObj2.setWatcher(watcher);
    ctObj2.setHandler(handler);

    ControlThread ctObj("ctObj");
//    ctObj.setPath("ctObj");
    ctObj.setWatcher(watcher2);
    ctObj.setHandler(handler);

    char cmd;
    bool bExit = false;
    while(!bExit){
        std::cin >> cmd;
        switch(cmd){
        case '1':
            ctObj2.start();
            ctObj.start();
            break;
        case '2':
            ctObj2.pause();
            ctObj.pause();
            break;
        case '3':
            ctObj2.resume();
            ctObj.resume();
            break;
        case '0':
            ctObj2.stop();
            ctObj.stop();
            bExit = true;
            break;
        default:
            ctObj2.stop();
            ctObj.stop();
            bExit = true;
            break;
        }
    }
}
