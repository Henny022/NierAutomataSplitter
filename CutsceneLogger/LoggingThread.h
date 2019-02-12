//
// Created by henny on 04.02.2019.
//

#ifndef NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
#define NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H

#include <iostream>
#include <iomanip>
#include <atomic>
#include <fstream>
#include <chrono>

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
        auto startTime = std::chrono::system_clock::now();
        auto cstartT = std::chrono::system_clock::to_time_t(startTime);
        logfile << std::ctime(&cstartT) << std::endl;

        bool currentIsCutscenePlaying;
        bool previousIsCutscenePlaying = false;
        std::string currentCutsceneName;
        std::string previousCutsceneName;
        //std::string currentPhaseName;
        //std::string previousPhaseName;
        std::string currentDelayedPhaseName;
        std::string previousDelayedPhaseName;
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

            //auto nowTime = std::chrono::system_clock::now();
            //auto t =(nowTime - startTime).count();

            // log cutscene
            currentIsCutscenePlaying = memoryHandler.isCutscenePlaying();
            if (currentIsCutscenePlaying && !previousIsCutscenePlaying)
            {
                currentCutsceneName = settings.getSettingString(memoryHandler.getCurrentCutscene());
                logfile << "Cutscene: " << currentCutsceneName << std::endl;
            }

            // log phase
            //currentPhaseName = memoryHandler.getCurrentPhase();
            //if (currentPhaseName != previousPhaseName)
            //{
            //    logfile << "Phase: " << currentPhaseName << " at t+" << t << "ms" << std::endl;
            //}

            // log delayed phase
            currentDelayedPhaseName = memoryHandler.getDelayedPhase();
            if (currentDelayedPhaseName != previousDelayedPhaseName)
            {
                logfile << "Delayed Phase: " << currentDelayedPhaseName << std::endl;
            }

            //if (!abortSignal)
            //{
            //    std::cout << "\rCutscene: " << std::left << std::setfill(' ') << std::setw(60)
            //              << currentCutsceneName.substr(0, 60)
            //              << " | Phase: " << std::left << std::setfill(' ') << std::setw(39)
            //              << currentPhaseName
            //              << std::flush;
            //}

            previousIsCutscenePlaying = currentIsCutscenePlaying;
            previousCutsceneName = currentCutsceneName;
            //previousPhaseName = currentPhaseName;
            previousDelayedPhaseName = currentDelayedPhaseName;
        }
        std::cout << "disconnecting" << std::endl;
        memoryHandler.disconnect();
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
