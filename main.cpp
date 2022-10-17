#include <Windows.h>

DWORD WINAPI ThreadMain(LPVOID lpThreadParameter) {
	return 0;
}

int main() {
	HANDLE hThread = CreateThread(
		0,
		0,
		ThreadMain,
		0,
		0,
		0
	);
		 
}