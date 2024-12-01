#include "header.h"

namespace dx
{
	DWORD NoBuffer = 0;
	DWORD UseFlip = 0;
	DWORD UseThrottle = 0;
	DWORD BPP = 0;
	DWORD time = 0;

	LPDIRECTDRAWSURFACE MatchFlip(WRAP* wp, LPDIRECTDRAWSURFACE in) {
		if (in && wp) {
			if (in == wp->dd_parent->fake[0]) return wp->dd_parent->fake[wp->dd_parent->flip];
			if (in == wp->dd_parent->fake[1]) return wp->dd_parent->fake[!wp->dd_parent->flip];
		}
		return in;
	}

	HRESULT Flush(WRAP* wp, LPDIRECTDRAWSURFACE fk, LPRECT rect, DWORD pal, DWORD dwFlags) {
		HRESULT hResult = DD_OK;
		DWORD now = 0;
		DWORD x = rect ? rect->left : 0;
		DWORD y = rect ? rect->top : 0;
		DWORD w = rect ? rect->right - rect->left : wp->dd_parent->width;
		DWORD h = rect ? rect->bottom - rect->top : wp->dd_parent->height;

		if (UseThrottle && pal) { // Palette is capped at 60 FPS (16ms)
			now = GetTickCount(); 
			if (now - time < 16) { WARN("DROP"); /* Sleep(1); */ return hResult; }
			time = now;
		}

		while (fk->lpVtbl->GetBltStatus(fk, DDGBS_ISBLTDONE) != DD_OK) Sleep(1);
		HDC src, dest = NULL;
		fk->lpVtbl->GetDC(fk, &src);
		if (NoBuffer) {
			if ((hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->GetDC(wp->dd_parent->real[wp->dd_parent->caps], &dest)) == DDERR_SURFACELOST) {
			       wp->dd_parent->real[0]->lpVtbl->Restore(wp->dd_parent->real[0]); // Restore() should only be called on primary surface
			       hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->GetDC(wp->dd_parent->real[wp->dd_parent->caps], &dest);
			}
		} else {
			hResult = wp->dd_parent->buffer->lpVtbl->GetDC(wp->dd_parent->buffer, &dest);
		}
		if (SUCCEEDED(hResult)) BitBlt(dest, x, y, w, h, src, x, y, SRCCOPY);
		fk->lpVtbl->ReleaseDC(fk, src);
		if (NoBuffer) {
			wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->ReleaseDC(wp->dd_parent->real[wp->dd_parent->caps], dest);
		} else {
			wp->dd_parent->buffer->lpVtbl->ReleaseDC(wp->dd_parent->buffer, dest);
			if (wp->dd_parent->clipper) { // BitFast does not support clipper
				if ((hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->Blt(wp->dd_parent->real[wp->dd_parent->caps], rect, wp->dd_parent->buffer, rect, NULL, NULL)) == DDERR_SURFACELOST) {
					wp->dd_parent->real[0]->lpVtbl->Restore(wp->dd_parent->real[0]); // Restore() should only be called on primary surface
					hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->Blt(wp->dd_parent->real[wp->dd_parent->caps], rect, wp->dd_parent->buffer, rect, NULL, NULL);
				}
			} else {
				if ((hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->BltFast(wp->dd_parent->real[wp->dd_parent->caps], x, y, wp->dd_parent->buffer, rect, DDBLTFAST_NOCOLORKEY)) == DDERR_SURFACELOST) {
					wp->dd_parent->real[0]->lpVtbl->Restore(wp->dd_parent->real[0]); // Restore() should only be called on primary surface
					hResult = wp->dd_parent->real[wp->dd_parent->caps]->lpVtbl->BltFast(wp->dd_parent->real[wp->dd_parent->caps], x, y, wp->dd_parent->buffer, rect, DDBLTFAST_NOCOLORKEY);
				}
			}
		}
		if (SUCCEEDED(hResult) && wp->dd_parent->caps) hResult = wp->dd_parent->real[0]->lpVtbl->Flip(wp->dd_parent->real[0], NULL, dwFlags);
		INFO("  Flush fake %d to real rect %08X pal %d @ %08X\n", fk == wp->dd_parent->fake[0] ? 0 : fk == wp->dd_parent->fake[1] ? 1 : -1, rect, pal, now);
		return hResult;
	}
}
