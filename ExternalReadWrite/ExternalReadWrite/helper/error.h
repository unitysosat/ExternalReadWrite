/**
 * error.h
 *
 * nt windows kernel vm errors
 *
 * @author unitysosat (aka inst3ad)
 * @date 14.03.2025
 * @license MIT License
 */

#pragma once

#include "../includes.h"

const char* get_error_name(DWORD error) {
    static const std::unordered_map<DWORD, const char*> error_names = {
        {ERROR_SUCCESS, "ERROR_SUCCESS"},
        {ERROR_INVALID_FUNCTION, "ERROR_INVALID_FUNCTION"},
        {ERROR_FILE_NOT_FOUND, "ERROR_FILE_NOT_FOUND"},
        {ERROR_ACCESS_DENIED, "ERROR_ACCESS_DENIED"},
        {ERROR_NOACCESS, "ERROR_NOACCESS"},
        {ERROR_PARTIAL_COPY, "ERROR_PARTIAL_COPY"},
        {ERROR_INVALID_HANDLE, "ERROR_INVALID_HANDLE"},
        {ERROR_INVALID_PARAMETER, "ERROR_INVALID_PARAMETER"},
    };

    auto it = error_names.find(error);
    if (it != error_names.end()) {
        return it->second;
    }
    return "UNKNOWN_ERROR";
}
