#include "header.h"

namespace dx
{
	DWORD NoBuffer = 0;
	DWORD UseFlip = 0;
	DWORD UseThrottle = 0;

	DWORD enabled = 0;
	DWORD caps = 0; // Flip capability
	DWORD write = 0;
	DWORD flip = 0;
	DWORD time = 0;
	DWORD width = 0, height = 0, bpp = 0;
	LPDIRECTDRAWPALETTE palette = NULL;
	LPDIRECTDRAWSURFACE real[2] = {NULL}, fake[2] = {NULL}, buffer = NULL;

	LPDIRECTDRAWSURFACE MatchFlip(LPDIRECTDRAWSURFACE in) {
		if (in != NULL) {
			if (in == fake[0]) return fake[flip];
			if (in == fake[1]) return fake[!flip];
		}
		return in;
	}

	HRESULT Flush(LPDIRECTDRAWSURFACE fk, DWORD pal, DWORD dwFlags) {
		HRESULT hResult = DD_OK;
		DWORD now = 0;

		if (UseThrottle && pal) { // Palette is capped at 60 FPS (16ms)
			now = GetTickCount(); 
			if (now - time < 16) { WARN("DROP"); /* Sleep(1); */ return hResult; }
			time = now;
		}

		while (fk->lpVtbl->GetBltStatus(fk, DDGBS_ISBLTDONE) != DD_OK) Sleep(1);
		HDC src, dest = NULL;
		fk->lpVtbl->GetDC(fk, &src);
		if (!NoBuffer) {
			buffer->lpVtbl->GetDC(buffer, &dest);
		} else {
			if ((hResult = real[caps]->lpVtbl->GetDC(real[caps], &dest)) == DDERR_SURFACELOST) {
			       real[0]->lpVtbl->Restore(real[0]); // Restore() should only be called on primary surface
			       hResult = real[caps]->lpVtbl->GetDC(real[caps], &dest);
			}
		}
		if (SUCCEEDED(hResult)) BitBlt(dest, 0, 0, width, height, src, 0, 0, SRCCOPY);
		fk->lpVtbl->ReleaseDC(fk, src);
		if (!NoBuffer) {
			buffer->lpVtbl->ReleaseDC(buffer, dest);
			if ((hResult = real[caps]->lpVtbl->BltFast(real[caps], 0, 0, buffer, NULL, DDBLTFAST_NOCOLORKEY)) == DDERR_SURFACELOST) {
			       real[0]->lpVtbl->Restore(real[0]); // Restore() should only be called on primary surface
			       hResult = real[caps]->lpVtbl->BltFast(real[caps], 0, 0, buffer, NULL, DDBLTFAST_NOCOLORKEY);
			}
		} else {
			real[caps]->lpVtbl->ReleaseDC(real[caps], dest);
		}
		if (SUCCEEDED(hResult) && caps) hResult = real[0]->lpVtbl->Flip(real[0], NULL, dwFlags);
		INFO("  Flush from fake %d to real by %d @ %08X\n", fk == fake[0] ? 0 : fk == fake[1] ? 1 : -1, pal, now);
		return hResult;
	}
}
