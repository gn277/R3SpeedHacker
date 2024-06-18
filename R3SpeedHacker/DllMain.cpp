#include "SpeedHacker/SpeedHacker.h"


void InitializeSpeedHacker()
{
	speedhacker = std::make_shared<SpeedHacker>();

	speedhacker->InitializeSpeedHacker();
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