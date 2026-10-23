#pragma once
#include <windows.h>
#include <tlhelp32.h>



//self explanatory
inline DWORD getPid(const wchar_t* procName) {
	DWORD pid = 0;
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) return 0;

	PROCESSENTRY32W entry{};
	entry.dwSize = sizeof(entry);
	if (Process32FirstW(snap, &entry)) {
		do {
			if (!_wcsicmp(entry.szExeFile, procName)) {
				pid = entry.th32ProcessID;
				break;
			}
		} while (Process32NextW(snap, &entry));
	}
	CloseHandle(snap);
	return pid;
}


//READ AND WRITE

template<typename T>
bool read(HANDLE process, uintptr_t address, T& out) {
	SIZE_T bytesRead = 0;
	return ReadProcessMemory(process, (LPCVOID)address, &out,
sizeof(T), &bytesRead) && bytesRead == sizeof(T);
}

template<typename T>
bool write(HANDLE process, uintptr_t address, T value) {
	SIZE_T bytesWritten = 0;
	return WriteProcessMemory(process, (LPVOID)address, &value,
		sizeof(T), &bytesWritten) && bytesWritten == sizeof(T);
}

inline uintptr_t readPtr(HANDLE process, uintptr_t address) {
	uint32_t ptr = 0;
	if (!read(process, address, ptr)) return 0;
	return ptr;
	//the games 32 bit: 4-byte pointers
}

//getting base address of a module
inline uintptr_t getModuleBase(HANDLE process, const wchar_t* moduleName) {
uintptr_t baseAddress = 0;
HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessId(process));
	if (snap == INVALID_HANDLE_VALUE) return 0;

	MODULEENTRY32W entry{};
	entry.dwSize = sizeof(entry);
	if (Module32FirstW(snap, &entry)) {
		do {
			if (!_wcsicmp(entry.szModule, moduleName)) {
				baseAddress = (uintptr_t)entry.hModule;
				break;
			}
		} while (Module32NextW(snap, &entry));
	}
	CloseHandle(snap);
	return baseAddress;
}