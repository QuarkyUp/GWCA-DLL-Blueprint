#include <Windows.h>

#include "GWCA-Public/GWCA/GWCA.h"
#include "GWCA-Public/GWCA/Managers/AgentMgr.h"
#include "GWCA-Public/GWCA/GameEntities/Agent.h"

void PrintCoords() {
	GW::Agent* player = GW::Agents::GetPlayer();
	printf("Player: %f %f", player->pos.x, player->pos.y);
}

int main() {
	AllocConsole();
	FILE* fh;
	freopen_s(&fh, "CONOUT$", "w", stdout);
	freopen_s(&fh, "CONOUT$", "w", stderr);
	SetConsoleTitleA("GWCA++ Debug Console");

	PrintCoords();

	FreeConsole();
}

DWORD WINAPI init(HMODULE hModule) {

	main();

	GW::Terminate();
	FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);

	return 0;
}

BOOL WINAPI DllMain(_In_ HMODULE _HDllHandle, _In_ DWORD _Reason, _In_opt_ LPVOID _Reserved) {
	if (_Reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(_HDllHandle);
		
		if (*(DWORD*)0x00DE0000 != NULL) {
			MessageBoxA(0, "Error: Guild Wars already injected!", "GWCA++", 0);
			FreeLibraryAndExitThread(_HDllHandle, EXIT_SUCCESS);
		}

		if (!GW::Initialize()) {
			return FALSE;
		}		
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, _HDllHandle, 0, 0);
	}
	return TRUE;
}

