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
	time_t curTime = std::chrono::system_clock::to_time_t(begin);
	const time_t period = 5;
	time_t endTime = beginTime + liveTime;

	bool flag = true;
	for  (time_t curTime = beginTime; curTime != endTime; )
	{
		auto tmp = std::chrono::system_clock::now();
		curTime = std::chrono::system_clock::to_time_t(tmp);
		time_t spendTimeTillBegin = curTime - beginTime;
		
		if (flag && spendTimeTillBegin && spendTimeTillBegin % period == 0) {
			ctime_s(str, sizeof str, &curTime);
			std::cout << str << std::endl;
			flag = false;
		}
		else if (spendTimeTillBegin % period) {
			flag = true;
		}
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