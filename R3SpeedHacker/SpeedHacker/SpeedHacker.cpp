#include "SpeedHacker.h"

std::shared_ptr<SpeedHacker> speedhacker = nullptr;


SpeedHacker::SpeedHacker()
{
}

SpeedHacker::~SpeedHacker()
{
}

DWORD WINAPI SpeedHacker::SelfGetTickCount()
{
    auto original_tick_count = speedhacker->pfnGetTickCount();
    return static_cast<DWORD>(original_tick_count * speedhacker->GetSpeedRatio());
}

ULONGLONG WINAPI SpeedHacker::SelfGetTickCount64()
{
    auto original_tick_count64 = speedhacker->pfnGetTickCount64();
    return static_cast<ULONGLONG>(original_tick_count64 * speedhacker->GetSpeedRatio());
}

BOOL WINAPI SpeedHacker::SelfQueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount)
{
    BOOL result = speedhacker->pfnQueryPerformanceCounter(lpPerformanceCount);
    if (result)
        lpPerformanceCount->QuadPart = static_cast<LONGLONG>(lpPerformanceCount->QuadPart * speedhacker->GetSpeedRatio());

    return result;
}

double SpeedHacker::GetSpeedRatio()
{
    return this->_speed_ratio;
}

void SpeedHacker::SetSpeedRatio(double speed_ratio)
{
    this->_speed_ratio = speed_ratio;
}

bool SpeedHacker::InitializeSpeedHacker()
{
    this->pfnGetTickCount = (fpGetTickCount)::GetProcAddress(::GetModuleHandleA("KERNEL32.dll"), "GetTickCount");
    this->pfnGetTickCount64 = (fpGetTickCount64)::GetProcAddress(::GetModuleHandleA("KERNEL32.dll"), "GetTickCount64");
    this->pfnQueryPerformanceCounter = (fpQueryPerformanceCounter)::GetProcAddress(::GetModuleHandleA("KERNEL32.dll"), "QueryPerformanceCounter");

    //参数判断
    if (!this->pfnGetTickCount || !this->pfnGetTickCount64 || !this->pfnQueryPerformanceCounter)
        return false;

    //初始化 Detours 并下Hook
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)this->pfnGetTickCount, SpeedHacker::SelfGetTickCount);
    DetourAttach(&(PVOID&)this->pfnGetTickCount64, SpeedHacker::SelfGetTickCount64);
    DetourAttach(&(PVOID&)this->pfnQueryPerformanceCounter, SpeedHacker::SelfQueryPerformanceCounter);
    DetourTransactionCommit();

    return true;
}
