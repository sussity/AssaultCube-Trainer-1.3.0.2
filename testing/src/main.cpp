#include <iostream>
#include "memory.h"




int main() {

	DWORD pid = getPid(L"ac_client.exe");

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); 
	if (!hProcess) {
		printf("OpenProcess failed: %lu\n", GetLastError());
	}
	else {
		printf("Found AssaultCube 1.3.0.2");
	}




	return 0;
}