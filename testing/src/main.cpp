#include <iostream>
#include "memory.h"




int main() {

	DWORD pid = getPid(L"ac_client.exe");

	if (!pid) { printf("Game not running\n"); return 1; }

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); 


	if (!hProcess) {
		printf("OpenProcess failed: %lu\n", GetLastError()); return 1;
	 }
	printf("Found AssaultCube 1.3.0.2\n");


	uintptr_t moduleBase = getModuleBase(hProcess, L"ac_client.exe");

	printf("Module base: 0x%llX\n", (unsigned long long)moduleBase);


	std::cin.get();
	CloseHandle(hProcess);
	return 0;
}