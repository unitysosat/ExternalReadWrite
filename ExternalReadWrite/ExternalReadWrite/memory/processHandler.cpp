/**
 * processHandler.cpp
 *
 * Realize pid_for_name, get_base_address, open_handle functions
 *
 * @author unitysosat (aka inst3ad)
 * @date 14.03.2025
 * @license MIT License
 */

#include "processHandler.h"

DWORD pid_for_name(const char* processName) {
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe)) {
            while (Process32Next(hSnapshot, &pe)) {
                if (strcmp(pe.szExeFile, processName) == 0) {
                    pid = pe.th32ProcessID;
                    break;
                }
            }
        }
        CloseHandle(hSnapshot);
    }
    return pid;
}

uintptr_t get_base_address(DWORD pid, const char* moduleName) {
    uintptr_t baseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 moduleEntry;
        moduleEntry.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &moduleEntry)) {
            while (Module32Next(hSnapshot, &moduleEntry)) {
                if (_stricmp(moduleEntry.szModule, moduleName) == 0) {
                    baseAddress = (uintptr_t)moduleEntry.modBaseAddr;
                    break;
                }
            }
        }
        CloseHandle(hSnapshot);
    }
    return baseAddress;
}

HANDLE open_handle(const char* targetProcessName, DWORD& _pid) {
    DWORD pid = pid_for_name(targetProcessName);
    if (pid == 0) {
        std::cerr << "process not found\n";
        return HANDLE();
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!hProcess) {
        std::cerr << "failed to open descriptor with nt kernel privelegies\n";
        return HANDLE();
    }

    _pid = pid;

    return hProcess;
}