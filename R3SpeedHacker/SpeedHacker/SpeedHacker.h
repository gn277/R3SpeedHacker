#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

#include <detours.h>


class SpeedHacker
{
private:
	//变速比例
	double _speed_ratio = 10.f;

public:
	SpeedHacker();
	~SpeedHacker();

private:
	//GetTickCount原始函数指针(KERNEL32.dll)
	typedef DWORD(WINAPI* fpGetTickCount)();
	fpGetTickCount pfnGetTickCount = nullptr;
	//拦截后的 GetTickCount 函数
	static DWORD WINAPI SelfGetTickCount();

	//GetTickCount64原始函数指针(KERNEL32.dll)
	typedef ULONGLONG(WINAPI* fpGetTickCount64)();
	fpGetTickCount64 pfnGetTickCount64 = nullptr;
	//拦截后的 GetTickCount64 函数
	static ULONGLONG WINAPI SelfGetTickCount64();

	//QueryPerformanceCounter原始函数指针(KERNEL32.dll)
	typedef BOOL(WINAPI* fpQueryPerformanceCounter)(LARGE_INTEGER*);
	fpQueryPerformanceCounter pfnQueryPerformanceCounter = nullptr;
	//拦截后的 QueryPerformanceCounter 函数
	static BOOL WINAPI SelfQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

public:
	//获取变速倍率
	double GetSpeedRatio();
	//设置变速倍率
	void SetSpeedRatio(double speed_ratio);

public:
	bool InitializeSpeedHacker();

};


extern "C" std::shared_ptr<SpeedHacker> speedhacker;
