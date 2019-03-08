//
// Created by henny on 17.02.2018.
//

#ifndef NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H
#define NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H


#include <windows.h>
#include <tlhelp32.h>
#include <utility>

class MemoryHandler
{
private:
    HANDLE _process;
	std::string _filename;
protected:

    template<typename Type>
    Type get(const uint64_t address)
    {
        Type buffer;
        if (connected && ReadProcessMemory(_process, reinterpret_cast<LPVOID>(address), &buffer, sizeof(buffer), nullptr))
        {
        }
        else
        {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
				throw std::runtime_error("connection error");
            }
        }
        return buffer;
    }

    template<size_t length>
    std::string getString(const uint64_t address)
    {
        char buffer[length + 1];
        if (connected && ReadProcessMemory(_process, reinterpret_cast<LPVOID>(address), &buffer, length, nullptr))
        {
            buffer[length] = '\0';
        }
        else
        {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
				throw std::runtime_error("connection error");
            }
        }
        return std::string(buffer);
    }

    template<typename Type>
    void set(const uint64_t address, Type value)
    {
        if (connected && WriteProcessMemory(_process, reinterpret_cast<LPVOID>(address), &value, sizeof(value), nullptr))
        {
        }
        else
        {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
				throw std::runtime_error("connection error");
            }
        }
    }

public:
    volatile bool connected = false;

    explicit MemoryHandler(std::string filename) : _process(nullptr), _filename(std::move(filename))
	{
	}

    bool connect()
    {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(snapshot, &entry) == TRUE)
        {
            while (Process32Next(snapshot, &entry) == TRUE)
            {
                if (strcmp(entry.szExeFile, _filename.c_str()) == 0)
                {
                    _process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                    connected = true;
                    std::cout << "Connected to " << _filename << " process " << entry.th32ProcessID << std::endl;
                    return true;
                }
            }
        }
        return false;
    }

    void disconnect()
    {
        if (!connected)
        {
            return;
        }
        CloseHandle(_process);
        connected = false;
        std::cout << "Disconnected from " << _filename << " process" << std::endl;
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H
