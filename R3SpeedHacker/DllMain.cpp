#include "SpeedHacker/SpeedHacker.h"


void InitializeSpeedHacker()
{
	auto speedhacker = SpeedHacker::GetInstance();
	if (!speedhacker->InitializeSpeedHacker())
		::MessageBoxA(::GetActiveWindow(), "初始化加速失败", "Error", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		InitializeSpeedHacker();
		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}