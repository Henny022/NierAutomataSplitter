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

        bool currentIsCutscenePlaying;
        bool previousIsCutscenePlaying = false;
        std::string currentCutsceneName;
        std::string previousCutsceneName;
        std::string currentPhaseName;
        std::string previousPhaseName;
        while (!abortSignal)
        {
            // check connection
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

            // log cutscene
            currentIsCutscenePlaying = memoryHandler.isCutscenePlaying();
            if (currentIsCutscenePlaying && !previousIsCutscenePlaying)
            {
                std::cout << "\r"
                          << "                                                                                                     "
                          << "\r";
                currentCutsceneName = settings.getSettingString(memoryHandler.getCurrentCutscene());
                std::cout << "Cutscene: " << currentCutsceneName << (currentCutsceneName == previousCutsceneName ? " !DUPLICATE!" : "");
                logfile << "Cutscene: " << currentCutsceneName << std::endl;
            }
            else if (!currentIsCutscenePlaying && previousIsCutscenePlaying)
            {
                //std::cout << "\r" << "                                                                                                     " << "\r";
            }

            // log phase
            currentPhaseName = memoryHandler.getCurrentPhase();
            if(currentPhaseName != previousPhaseName)
            {
                logfile << "Phase: " << currentPhaseName << std::endl;
            }

            previousIsCutscenePlaying = currentIsCutscenePlaying;
            previousCutsceneName = currentCutsceneName;
            previousPhaseName = currentPhaseName;
        }
        memoryHandler.disconnect();
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
