#include "controlThread.h"

ControlThread::ControlThread()
{
    bStart = false;
    bStop = false;
}

ControlThread::ControlThread(const std::string& path)
{
    if(!path.empty() && path != m_Path){
        m_Path = path;
    }
    bStart = false;
    bStop = false;
}

ControlThread::~ControlThread()
{
    if(m_Thread.joinable())m_Thread.join();
    fswatcher_destroy(m_Watcher);
}

void ControlThread::threadMain()
{
    while(!bStop){
        while(!bStart){
            std::unique_lock<std::mutex> lk(m_Mutex);
            m_Cv.wait(lk);
            lk.unlock();
        }
        while(bStart && !bStop){
            // do something ...
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Working...path =" << m_Path << std::endl;
            fswatcher_poll( m_Watcher, &m_Handler, 0x0 );
        }
    }
}

void ControlThread::setWatcher(fswatcher_t watcher)
{
    m_Watcher = std::move(watcher);
}

void ControlThread::setHandler(fswatcher_event_handler handler)
{
    m_Handler = std::move(handler);
}

void ControlThread::setPath(const std::string& path)
{
    m_Path = path;
}

bool ControlThread::initThread()
{
    if(!bInitialized){
        m_Thread = std::thread(&ControlThread::threadMain, this);
        bInitialized = true;
    }
    return bInitialized;
}

void ControlThread::start()
{
    std::lock_guard<std::mutex> lg(m_Mutex);
    if(!bInitialized){
        initThread();
    }
    // recheck
    if(bInitialized){
        bStart = true;
        m_Cv.notify_one();
    }
}


void ControlThread::pause()
{
    std::lock_guard<std::mutex> lg(m_Mutex);
    bStart = false;
}

void ControlThread::resume()
{
    std::lock_guard<std::mutex> lg(m_Mutex);
    bStart = true;
    m_Cv.notify_one();
}

void ControlThread::stop()
{
    std::lock_guard<std::mutex> lg(m_Mutex);
    bStart = false;
    bStop = true;
    m_Cv.notify_one(); //???/
}
