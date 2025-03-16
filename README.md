# External Memory Reader/Writer

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Read and write memory external process with using Win api. supports working with x86(32-bit) and x64(64-bit) process, including apps and games.

## Features

- **Module searcher**: Getting the base addresses of modules (for example, `GameAssembly.dll`).
- **Supports 32/64 бит**: works with 32-bit, and with 64-bit process.
- **Integration with NT Kernel**: Using low-level Win api functions to work with memory `ReadProcessMemory`, `WriteProcessMemory` they all use `NtReadVirtualMemory` and `NtWriteVirtualMemory` internally).
