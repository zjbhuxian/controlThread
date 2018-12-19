/*--------------------------------------------------------------------
 * Created by zjbhuxian. 2018/12/19
 * A sample class using std::thread to support
 * start() -- start a thread, doing something
 * pause() -- pause a thread
 * resume() -- resume a thread when the thread paused...
 * stop() -- stop a thread, destory it...
 * email: zjbhuxian@gmail.com
 *-------------------------------------------------------------------*/
#ifndef __CONTROLTHREAD_H__
#define __CONTROLTHREAD_H__
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "fswatcher.h"

class ControlThread
{
public:
    ControlThread();
    ControlThread(const std::string& path);
    ~ControlThread();
    void setPath(const std::string& path);
    void threadMain();
    bool initThread();
    void start();
    void pause();
    void resume();
    void stop();
    void setWatcher(fswatcher_t watcher);
    void setHandler(fswatcher_event_handler handler);

private:
    fswatcher_t m_Watcher;
    fswatcher_event_handler m_Handler;
    std::string m_Path;
    std::mutex m_Mutex;
    std::condition_variable m_Cv;
    bool bInitialized;
    bool bStart;
    bool bStop;
    std::thread m_Thread;
};
#endif // __CONTROLTHREAD_H__
