#include <iostream>
#include <fstream>
#include <ctime>
#include "NierAutomataMemoryHandler.h"
#include "LiveSplitSettings.h"

int main()
{
    NierAutomataMemoryHandler memoryHandler;
    LiveSplitSettings settings;
    std::ofstream logFile("log.txt", std::ios::out | std::ios::app);
    std::time_t result = std::time(nullptr);
    logFile << std::asctime(std::localtime(&result)) << std::endl;
    while (true)
    {
        while (!memoryHandler.connect());
        logFile << "connected" << std::endl;
        bool previous = false;
        while (memoryHandler.connected)
        {
            bool current = memoryHandler.isCutscenePlaying();
            std::string previousCutscene;
            if (current && !previous)
            {
                std::cout << "\r"
                          << "                                                                                                     "
                          << "\r";
                std::string currentCutscene = settings.getSettingString(memoryHandler.getCurrentCutscene());
                std::cout << currentCutscene << (currentCutscene == previousCutscene ? " !DUPLICATE!" : "");
                logFile << currentCutscene << std::endl;
            } else if (!current && previous)
            {
                //std::cout << "\r" << "                                                                                                     " << "\r";
            }
            previous = current;
        }
        logFile << "disconnected" << std::endl;
        Sleep(1000);
    }
}