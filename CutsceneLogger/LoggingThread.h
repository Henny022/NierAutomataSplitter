//
// Created by henny on 04.02.2019.
//

#ifndef NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
#define NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H

#include <iostream>
#include <iomanip>
#include <atomic>
#include <fstream>
#include <ctime>

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
        abortSignal = false;
        logfile = std::ofstream("log.txt", std::ios::out | std::ios::app);
    }

    void abort()
    {
        abortSignal = true;
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
                currentCutsceneName = settings.getSettingString(memoryHandler.getCurrentCutscene());
                logfile << "Cutscene: " << currentCutsceneName << std::endl;
            }

            // log phase
            currentPhaseName = memoryHandler.getCurrentPhase();
            if (currentPhaseName != previousPhaseName && !currentPhaseName.empty())
            {
                logfile << "Phase: " << currentPhaseName << std::endl;
            }

            if (!abortSignal)
            {
                std::cout << "\rCutscene: " << std::left << std::setfill(' ') << std::setw(60)
                          << currentCutsceneName.substr(0, 60)
                          << " | Phase: " << std::left << std::setfill(' ') << std::setw(39)
                          << currentPhaseName
                          << std::flush;
            }
            previousIsCutscenePlaying = currentIsCutscenePlaying;
            previousCutsceneName = currentCutsceneName;
            previousPhaseName = currentPhaseName;
        }
        std::cout << "disconnecting" << std::endl;
        memoryHandler.disconnect();
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
