/**
 * processMemory.h
 *
 * default winapi vm read/write
 *
 * @author unitysosat (aka inst3ad)
 * @date 14.03.2025
 * @license MIT License
 */

#pragma once

#include "../helper/error.h"

template <typename T>
T read(uintptr_t address) {
    T value;
    if (!ReadProcessMemory(targetProcess, (LPCVOID)address, &value, sizeof(T), nullptr)) {
        printf("failed to read memory at %p due to %s\n", (void*)address, get_error_name(GetLastError()));
        return T();
    }
    return value;
}

template <typename T>
bool write(uintptr_t address, const T& value) {
    if (!WriteProcessMemory(targetProcess, (LPVOID)address, &value, sizeof(T), nullptr)) {
        printf("failed to write memory at %p due to %d\n", (void*)address, get_error_name(GetLastError()));
        return false;
    }
    return true;
}
