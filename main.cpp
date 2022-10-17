#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>  
using namespace std;

DWORD WINAPI ThreadSaid(LPVOID lpThreadParameter) {
	
	char str[26];
	time_t liveTime =(*static_cast<int*>(lpThreadParameter));
	auto begin = std::chrono::system_clock::now();
	time_t beginTime = std::chrono::system_clock::to_time_t(begin);
	auto nowadays = begin;
	time_t curTime = std::chrono::system_clock::to_time_t(nowadays);
	time_t period = 5;
	auto delta = 0;

	while(true)
	{
		//cout << "\tdelta " << delta << endl;
		delta = curTime - beginTime + period;
		if (delta > liveTime) {
			break;
		}
		Sleep(period * 1000);
		nowadays = std::chrono::system_clock::now();
		curTime = std::chrono::system_clock::to_time_t(nowadays);
		ctime_s(str, sizeof str, &curTime);
		cout << str << endl;
	}

	while (true)
	{
		nowadays = std::chrono::system_clock::now();
		curTime = std::chrono::system_clock::to_time_t(nowadays);
		delta = curTime - beginTime;
		//cout << "#";
		if (delta >= liveTime) {
			break;
		}
	}
	cout << endl;
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