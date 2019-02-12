//
// Created by henny on 07.02.2018.
//

#ifndef NIERAUTOMATAPRACTICETOOL_MEMORYEDITOR_H
#define NIERAUTOMATAPRACTICETOOL_MEMORYEDITOR_H

#include "MemoryHandler.h"

class NierAutomataMemoryHandler : public MemoryHandler
{
public:
    float getGameSpeed()
    {
        return get<float>(0x14160E6D8);
    }

    float getX()
    {
        return get<float>(get<UINT_PTR>(0x1416053E8) + 0x50);
    }

    float getY()
    {
        return get<float>(get<UINT_PTR>(0x1416053E8) + 0x58);
    }

    float getZ()
    {
        return get<float>(get<UINT_PTR>(0x1416053E8) + 0x54);
    }

    void setGameSpeed(float speed)
    {
        set(0x14160E6D8, speed);
    }

    bool playerNameSetStatus()
    {
        return get<bool>(0x14147B4BC);
    }

    bool isLoading()
    {
        return get<bool>(0x14147BF50);
    }

    bool isWorldLoaded()
    {
        return get<bool>(0x14110ADC0);
    }

    bool isCutscenePlaying()
    {
        return get<bool>(0x141483974);
    }

    std::string getCurrentCutscene()
    {
        return getString<16>(get<UINT_PTR>(0x1419925E8) + 0x1f4);
    }

    std::string getCurrentPhase()
    {
        return getString<0x28>(0x141101d58);
    }

    std::string getDelayedPhase()
    {
        return getString<0x28>(0x141101d30);
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_MEMORYEDITOR_H
