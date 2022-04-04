#include "header.h"

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

	bool Flush(LPDIRECTDRAWSURFACE fk, DWORD to) {
		DWORD now = 0;
		if (to == 0) { // 60 FPS Max 16ms
			now = timeGetTime(); 
			if (now - time < 16) return false;
			time = now;
		}
		while (fk->lpVtbl->GetBltStatus(fk, DDGBS_ISBLTDONE) != DD_OK) Sleep(0);
		HDC src, dest;
		fk->lpVtbl->GetDC(fk, &src);
		if (real[to]->lpVtbl->GetDC(real[to], &dest) == DDERR_SURFACELOST) {
			real[to]->lpVtbl->Restore(real[to]);
			real[to]->lpVtbl->GetDC(real[to], &dest);
		}
		BitBlt(dest, 0, 0, width, height, src, 0, 0, SRCCOPY);
		real[to]->lpVtbl->ReleaseDC(real[to], dest);
		fk->lpVtbl->ReleaseDC(fk, src);
		INFO("Flush to real %d from fake %d @ %08X\n", to, fk == fake[0] ? 0 : fk == fake[1] ? 1 : -1, now);
		return true;
	}
}
