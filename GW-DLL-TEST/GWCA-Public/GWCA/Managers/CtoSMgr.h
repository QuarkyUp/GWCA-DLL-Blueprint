#pragma once

#include <Windows.h>

#include <GWCA\Utilities\Export.h>

namespace GW {
	namespace CtoS {
        // Send packet that uses only dword parameters, can copypaste most gwa2 sendpackets :D
		GWCA_API void SendPacket(DWORD size, ...);
        
        // Send a packet with a specific struct alignment, used for more complex packets.
		GWCA_API void SendPacket(DWORD size, void* buffer);

        template <class T>
        void SendPacket(T* packet) { SendPacket(sizeof(T), packet); }
    };
}
