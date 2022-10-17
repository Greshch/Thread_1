#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>  
using namespace std;

DWORD WINAPI ThreadSaid(LPVOID lpThreadParameter) {
	
	char str[26];
	int liveTime = *static_cast<int*>(lpThreadParameter);
	for(int i = 0 ;  i < liveTime; ++i)
	{
		Sleep(5 * 1000);
		auto nowadays = std::chrono::system_clock::now();
		std::time_t cur_time = std::chrono::system_clock::to_time_t(nowadays);
		ctime_s(str, sizeof str, &cur_time);
		cout << str << endl;
	}
	
	return 0;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cerr << "Lack of argumen error...code 101\n";
		return 101;
	}
	int times = atoi(argv[1]);
	HANDLE hSaid = CreateThread(
		0,
		0,
		ThreadSaid,
		&times,
		0,
		0
	);

	DWORD res =  WaitForSingleObject(hSaid, INFINITE);
	if (res == WAIT_TIMEOUT) {
		cout << "\nSaid thread was terminated\n";
		TerminateThread(hSaid, -1);
	}	
}