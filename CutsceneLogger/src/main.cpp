#define _CRT_SECURE_NO_WARNINGS

#include <thread>

#include "LoggingThread.h"

int main()
{
    LoggingThread loggingThread;
    std::thread thread(&LoggingThread::run, std::ref(loggingThread));
    std::cin.ignore();
    loggingThread.abort();
    thread.join();
}