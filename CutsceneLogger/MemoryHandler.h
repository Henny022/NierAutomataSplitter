//
// Created by henny on 17.02.2018.
//

#ifndef NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H
#define NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H


#include <windows.h>
#include <tlhelp32.h>

class MemoryHandler {
private:
    HANDLE process;
protected:

    template<typename type>
    type get(uint64_t address) {
        type buffer;
        if (connected && ReadProcessMemory(process, (LPVOID) address, &buffer, sizeof(buffer), nullptr)) {
        } else {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
                disconnect();
            }
            return type();
        }
        return buffer;
    }

    template<size_t length>
    std::string getString(uint64_t address) {
        char buffer[length + 1];
        if (connected && ReadProcessMemory(process, (LPVOID) address, &buffer, length, nullptr)) {
            buffer[length] = '\0';
        } else {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
                disconnect();
            }
            return "";
        }
        return std::string(buffer);
    }

    template<typename type>
    void set(uint64_t address, type value) {
        if (connected && WriteProcessMemory(process, (LPVOID) address, &value, sizeof(value), nullptr)) {
        } else {
            DWORD error = GetLastError();
            std::cout << "Error: " << error << std::endl;
            if (error == 299)
            {
                disconnect();
            }
        }
    }

public:
    bool connected = false;

    bool connect() {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(snapshot, &entry) == TRUE)
        {
            while (Process32Next(snapshot, &entry) == TRUE)
            {
                if (_stricmp(entry.szExeFile, "NieRAutomata.exe") == 0)
                {
                    process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                    connected = true;
                    std::cout << "Connected to NieR:Automata process" << std::endl;
                    return true;
                }
            }
        }
        return false;
    }

    void disconnect() {
        CloseHandle(process);
        connected = false;
        std::cout << "Disconnected from NieR:Automata process" << std::endl;
    }
};

#endif //NIERAUTOMATAPRACTICETOOL_MEMORYHANDLER_H
