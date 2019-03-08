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
	std::atomic_bool _abortSignal;
	NierAutomataMemoryHandler _memoryHandler;
	LiveSplitSettings _settings;
	std::ofstream _logfile;

public:

	LoggingThread()
	{
		_abortSignal = false;
		_logfile = std::ofstream("log.txt", std::ios::out | std::ios::app);
	}

	void abort()
	{
		_abortSignal = true;
	}

	void run()
	{
		auto startTime = std::chrono::system_clock::now();
		auto cstartT = std::chrono::system_clock::to_time_t(startTime);
		_logfile << std::ctime(&cstartT) << std::endl;
		//_logfile << "temp workaround for timestamp" << std::endl;

		bool previousIsCutscenePlaying = false;
		std::string currentCutsceneName;
		std::string previousDelayedPhaseName;
		while (!_abortSignal)
		{
			// check connection
			if (!_memoryHandler.connected)
			{
				std::cout << "trying to connect to NieR:Automata process" << std::endl;
				if (!_memoryHandler.connect())
				{
					std::cout << "cannot connect, retrying ..." << std::endl;
					Sleep(3000);
					continue;
				}
				_logfile << "connected" << std::endl;
			}
			try
			{
				// log cutscene
				bool currentIsCutscenePlaying = _memoryHandler.isCutscenePlaying();
				if (currentIsCutscenePlaying && !previousIsCutscenePlaying)
				{
					currentCutsceneName = _settings.getSettingString(_memoryHandler.getCurrentCutscene());
					_logfile << "Cutscene: " << currentCutsceneName << std::endl;
				}

				// log delayed phase
				std::string currentDelayedPhaseName = _memoryHandler.getDelayedPhase();
				if (currentDelayedPhaseName != previousDelayedPhaseName)
				{
					_logfile << "Delayed Phase: " << currentDelayedPhaseName << std::endl;
				}

				if (!_abortSignal)
				{
					std::cout << "\rCutscene: " << std::left << std::setfill(' ') << std::setw(60)
						<< currentCutsceneName.substr(0, 60)
						<< " | Phase: " << std::left << std::setfill(' ') << std::setw(39)
						<< currentDelayedPhaseName
						<< std::flush;
				}

				previousIsCutscenePlaying = currentIsCutscenePlaying;
				previousDelayedPhaseName = currentDelayedPhaseName;
			}
			catch (std::runtime_error& e)
			{
				_memoryHandler.disconnect();
			}
		}
		std::cout << "disconnecting" << std::endl;
		_memoryHandler.disconnect();
	}
};

#endif //NIERAUTOMATAPRACTICETOOL_LOGGINGTHREAD_H
