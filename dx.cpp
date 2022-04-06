#include "header.h"

#define USE_THROTTLE

namespace dx
{
	DWORD enabled = 0;
	DWORD write = 0;
	DWORD flip = 0;
	DWORD time = 0;
	DWORD width = 0, height = 0;
	LPDIRECTDRAWPALETTE palette = NULL;
	LPDIRECTDRAWSURFACE real[2] = {NULL}, fake[2] = {NULL};

	LPDIRECTDRAWSURFACE MatchFlip(LPDIRECTDRAWSURFACE in) {
		if (in == fake[0]) return fake[flip];
		else if (in == fake[1]) return fake[!flip];
		else return in;
	}

	HRESULT Flush(LPDIRECTDRAWSURFACE fk, DWORD to, DWORD dwFlags) {
		HRESULT hResult;
		DWORD now = 0;

#ifdef USE_THROTTLE
		if (to == 0) { // Palette is capped at 30 FPS (30ms)
			now = GetTickCount(); 
			if (now - time < 30) { WARN("DROP"); return DDERR_WASSTILLDRAWING; }
			time = now;
		}
#endif
		while (fk->lpVtbl->GetBltStatus(fk, DDGBS_ISBLTDONE) != DD_OK) Sleep(0);
		HDC src, dest;
		fk->lpVtbl->GetDC(fk, &src);
		while ((hResult = real[1]->lpVtbl->GetDC(real[1], &dest)) == DDERR_SURFACELOST) real[1]->lpVtbl->Restore(real[1]);
		BitBlt(dest, 0, 0, width, height, src, 0, 0, SRCCOPY);
		real[1]->lpVtbl->ReleaseDC(real[1], dest);
		fk->lpVtbl->ReleaseDC(fk, src);
		if (SUCCEEDED(hResult)) hResult = real[0]->lpVtbl->Flip(real[0], NULL, dwFlags);
		INFO("Flush to real %d from fake %d @ %08X\n", to, fk == fake[0] ? 0 : fk == fake[1] ? 1 : -1, now);
		return hResult;
	}
}
