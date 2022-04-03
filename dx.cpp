#include "header.h"

namespace dx
{
	DWORD enabled = 0;
	DWORD time = 0;
	DWORD width = 0, height = 0;
	LPDIRECTDRAWSURFACE realFront = NULL, realBack = NULL, fakeFront = NULL, fakeBack = NULL;
	LPDIRECTDRAWPALETTE palette = NULL;

	bool Update() {
		DWORD now = timeGetTime(); 
		// 60 FPS Max
		if (now - time > 15) {
			time = now;
			return true;
		}
		return false;
	}
}
