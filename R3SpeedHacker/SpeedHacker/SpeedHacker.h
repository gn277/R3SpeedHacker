#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

#include <detours.h>


class SpeedHacker
{
private:
	//���ٱ���
	double _speed_ratio = 10.f;

public:
	SpeedHacker();
	~SpeedHacker();

private:
	//GetTickCountԭʼ����ָ��(KERNEL32.dll)
	typedef DWORD(WINAPI* fpGetTickCount)();
	fpGetTickCount pfnGetTickCount = nullptr;
	//���غ�� GetTickCount ����
	static DWORD WINAPI SelfGetTickCount();

	//GetTickCount64ԭʼ����ָ��(KERNEL32.dll)
	typedef ULONGLONG(WINAPI* fpGetTickCount64)();
	fpGetTickCount64 pfnGetTickCount64 = nullptr;
	//���غ�� GetTickCount64 ����
	static ULONGLONG WINAPI SelfGetTickCount64();

	//QueryPerformanceCounterԭʼ����ָ��(KERNEL32.dll)
	typedef BOOL(WINAPI* fpQueryPerformanceCounter)(LARGE_INTEGER*);
	fpQueryPerformanceCounter pfnQueryPerformanceCounter = nullptr;
	//���غ�� QueryPerformanceCounter ����
	static BOOL WINAPI SelfQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);

public:
	//��ȡ���ٱ���
	double GetSpeedRatio();
	//���ñ��ٱ���
	void SetSpeedRatio(double speed_ratio);

public:
	bool InitializeSpeedHacker();

};


extern "C" std::shared_ptr<SpeedHacker> speedhacker;
