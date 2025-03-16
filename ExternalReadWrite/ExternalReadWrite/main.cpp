/**
 * main.cpp
 *
 * console subsystem entry point
 * open handle, destruct handle
 * example for read/write
 *
 * @author unitysosat (aka inst3ad)
 * @date 14.03.2025
 * @license MIT License
 */

#include "memory/processHandler.h"
#include "memory/processMemory.h"

HANDLE targetProcess = nullptr;

void destruct_handle() {
    CloseHandle(targetProcess);
    std::cout << "handle with pid " << targetProcess << " closed\n";
}

struct Vector3 {
    float x, y, z;
};

void thread(DWORD pid) {
    /* example */
    uintptr_t base = get_base_address(pid, /*name of module*/"GameAssembly.dll");
    if (!base) {
        std::cerr << "game assembly null\n";
        return;
    }
    uintptr_t typeinfo = read<uintptr_t>(base + 0x1690BAC);
    if (!typeinfo) {
        std::cerr << "typeinfo null\n";
        return;
    }
    uintptr_t staticfields = read<uintptr_t>(typeinfo + 0x5C);
    if (!staticfields) {
        std::cerr << "staticfields null\n";
        return;
    }
    uintptr_t battlecontrollerscript = read<uintptr_t>(staticfields + 0x1C);
    if (!battlecontrollerscript) {
        std::cerr << "bcs null\n";
        return;
    }
    uintptr_t player = read<uintptr_t>(battlecontrollerscript + 0x7C);
    if (!player) {
        std::cerr << "player null\n";
        return;
    }
    if (GetKeyState(VK_INSERT) & 0x8000) {
        //write with value 999
        write<int>(player + 0x10, 999);
        //read
        float speed = read<float>(player + 0x14);
    }
}

int main() {
    // name of process.
    const char* targetProcessName = "build.exe";

    DWORD pid;
    targetProcess = open_handle(targetProcessName, pid);
    if (!targetProcess) {
        return 1;
    }

    while (1) {
        if (GetKeyState(VK_END) & 0x8000) {
            destruct_handle();
        }
        thread(pid);
        Sleep(1);
    }

    return 0;
}