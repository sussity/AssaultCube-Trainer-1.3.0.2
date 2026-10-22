#pragma once
#include <windows.h>
#include <tlhelp32.h>


//self explanatory
DWORD getPid(const wchar_t* procName) {
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
		} while (Process32Next(snap, &entry));
	}
	CloseHandle(snap);
	return pid;
}


//READ AND WRITE

template<typename T>
T read(HANDLE process, uintptr_t address) {
	T value{};
	ReadProcessMemory(process, (LPCVOID)address, &value,
sizeof(T), nullptr);
	return value;
}

template<typename T>
T Write(HANDLE process, uintptr_t address, T value) {
	WriteProcessMemory(process, (LPVOID)address, &value,
		sizeof(T), nullptr);
}

inline uintptr_t readPtr(HANDLE process, uintptr_t address) {
	return (uintptr_t)read<uint32_t>(process, address);
	//the games 32 bit: 4-byte pointers
}