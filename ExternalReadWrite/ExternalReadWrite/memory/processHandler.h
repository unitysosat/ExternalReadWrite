/**
 * processHandler.h
 * 
 * Externs pid_for_name, get_base_address, open_handle functions, HANDLE targetProcess
 *
 * @author unitysosat (aka inst3ad)
 * @date 14.03.2025
 * @license MIT License
 */

#pragma once

#include "../includes.h"

extern HANDLE targetProcess;

DWORD pid_for_name(const char* processName);

uintptr_t get_base_address(DWORD pid, const char* moduleName);

HANDLE open_handle(const char* targetProcessName, DWORD& pid);