//
// Created by henny on 04.02.2019.
//

#ifndef NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
#define NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H

#include <iostream>
#include <atomic>
#include <fstream>

#include "LiveSplitSettings.h"
#include "NierAutomataMemoryHandler.h"

class LoggingThread
{
private:
    std::atomic_bool abortSignal;
    NierAutomataMemoryHandler memoryHandler;
    LiveSplitSettings settings;
    std::ofstream logfile;

public:

    LoggingThread()
    {
        logfile = std::ofstream("log.txt", std::ios::out | std::ios::app);
    }

    void abort()
    {
        abortSignal = true;
        std::cout << "aborting logging" << std::endl;
    }

    void run()
    {
        std::time_t result = std::time(nullptr);
        logfile << std::asctime(std::localtime(&result)) << std::endl;
        bool previous = false;
        bool current;
        std::string previousCutscene;
        std::string currentCutscene;
        while (!abortSignal)
        {
            if (!memoryHandler.connected)
            {
                std::cout << "trying to connect to NieR:Automata process" << std::endl;
                if (!memoryHandler.connect())
                {
                    std::cout << "cannot connect, retrying ..." << std::endl;
                    Sleep(1000);
                    continue;
                }
                logfile << "connected" << std::endl;
            }
            current = memoryHandler.isCutscenePlaying();
            if (current && !previous)
            {
                std::cout << "\r"
                          << "                                                                                                     "
                          << "\r";
                currentCutscene = settings.getSettingString(memoryHandler.getCurrentCutscene());
                std::cout << currentCutscene << (currentCutscene == previousCutscene ? " !DUPLICATE!" : "");
                logfile << currentCutscene << std::endl;
            }
            else if (!current && previous)
            {
                //std::cout << "\r" << "                                                                                                     " << "\r";
            }
            previous = current;
            previousCutscene = currentCutscene;
        }
        memoryHandler.disconnect();
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
