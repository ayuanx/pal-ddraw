#include "header.h"

namespace dd
{
	struct XVTBL
	{
		HRESULT (__stdcall * QueryInterface)( WRAP* This, const IID& riid, void** ppvObject );
		ULONG   (__stdcall * AddRef)( WRAP* This );
		ULONG   (__stdcall * Release)( WRAP* This );
		HRESULT (__stdcall * Compact)( WRAP* This );
		HRESULT (__stdcall * CreateClipper)( WRAP* This, DWORD dwFlags, LPDIRECTDRAWCLIPPER *lplpDDClipper, IUnknown *pUnkOuter);
		HRESULT (__stdcall * CreatePalette)( WRAP* This, DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE *lplpDDPalette, IUnknown *pUnkOuter);
		HRESULT (__stdcall * CreateSurface)( WRAP* This, LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE *lplpDDSurface, IUnknown *pUnkOuter );
		HRESULT (__stdcall * DuplicateSurface)( WRAP* This, LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE *lplpDupDDSurface );
		HRESULT (__stdcall * EnumDisplayModes)( WRAP* This, DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback );
		HRESULT (__stdcall * EnumSurfaces)( WRAP* This, DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback );
		HRESULT (__stdcall * FlipToGDISurface)( WRAP* This );
		HRESULT (__stdcall * GetCaps)( WRAP* This, LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps );
		HRESULT (__stdcall * GetDisplayMode)( WRAP* This, LPDDSURFACEDESC lpDDSurfaceDesc );
		HRESULT (__stdcall * GetFourCCCodes)( WRAP* This, LPDWORD lpNumCodes, LPDWORD lpCodes );
		HRESULT (__stdcall * GetGDISurface)( WRAP* This, LPDIRECTDRAWSURFACE *lplpGDIDDSurface );
		HRESULT (__stdcall * GetMonitorFrequency)( WRAP* This, LPDWORD lpdwFrequency );
		HRESULT (__stdcall * GetScanLine)( WRAP* This, LPDWORD lpdwScanLine );
		HRESULT (__stdcall * GetVerticalBlankStatus)( WRAP* This, BOOL *lpbIsInVB );
		HRESULT (__stdcall * Initialize)( WRAP* This, GUID *lpGUID );
		HRESULT (__stdcall * RestoreDisplayMode)( WRAP* This );
		HRESULT (__stdcall * SetCooperativeLevel)( WRAP* This, HWND hWnd, DWORD dwFlags );
		union
		{
			LPVOID dummy; // for use with an initializer list...
			HRESULT (__stdcall * SetDisplayMode1)( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP );
			HRESULT (__stdcall * SetDisplayMode2)( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags );
		};
		HRESULT (__stdcall * WaitForVerticalBlank)( WRAP* This, DWORD dwFlags, HANDLE hEvent );
		// v2
		HRESULT (__stdcall * GetAvailableVidMem)( WRAP* This, LPDDSCAPS lpDDCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree );
		// v4
		HRESULT (__stdcall * GetSurfaceFromDC)( WRAP* This, HDC hdc, LPDIRECTDRAWSURFACE4* lplpDDSurface );
		HRESULT (__stdcall * RestoreAllSurfaces)( WRAP* This );
		HRESULT (__stdcall * TestCooperativeLevel)( WRAP* This );
		HRESULT (__stdcall * GetDeviceIdentifier)( WRAP* This, LPDDDEVICEIDENTIFIER pDDDI, DWORD dwFlags );
		// v7
		HRESULT (__stdcall * StartModeTest)( WRAP* This, LPSIZE pModes, DWORD dwNumModes, DWORD dwFlags );
		HRESULT (__stdcall * EvaluateMode)( WRAP* This, DWORD dwFlags, DWORD  *pTimeout );
	};

	HRESULT __stdcall QueryInterface( WRAP* This, const IID& riid, void** ppvObject )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->QueryInterface( This->dd1, riid, ppvObject );
		INFO("QueryInterface DD %08X -> %08X (IID %08X)\n", This->dd1, *ppvObject, riid);
		if( SUCCEEDED( hResult ) ) Wrap( This->dd_parent, iid_to_vtbl( riid ), ppvObject );
		EPILOGUE( hResult );
	}

	ULONG __stdcall AddRef( WRAP* This )
	{
		PROLOGUE;
		ULONG dwCount = This->dd1->lpVtbl->AddRef( This->dd1 );
		EPILOGUE( dwCount );
	}

	ULONG __stdcall Release( WRAP* This )
	{ 	
		PROLOGUE;
		ULONG dwCount = WrapRelease( This );
		INFO("Release DD %08X dwCount %08X\n", This->dd1, dwCount);
		EPILOGUE( dwCount );
	}

	HRESULT __stdcall Compact( WRAP* This )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->Compact( This->dd1 );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall CreateClipper( WRAP* This, DWORD dwFlags, LPDIRECTDRAWCLIPPER *lplpDDClipper, IUnknown *pUnkOuter )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->CreateClipper( This->dd1, dwFlags, lplpDDClipper, pUnkOuter );
		INFO("CreateClipper dwFlags %08X -> %08X\n", dwFlags, *lplpDDClipper);
		if( SUCCEEDED( hResult ) )
		{
			Wrap( This->dd_parent, iid_to_vtbl( IID_IDirectDrawClipper ), (void**)lplpDDClipper );
		}
		EPILOGUE( hResult );
	}

	HRESULT __stdcall CreatePalette( WRAP* This, DWORD dwFlags, LPPALETTEENTRY lpColorTable, LPDIRECTDRAWPALETTE *lplpDDPalette, IUnknown *pUnkOuter )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->CreatePalette( This->dd1, dwFlags, lpColorTable, lplpDDPalette, pUnkOuter );
		INFO("CreatePalette dwFlags %08X -> %08X\n", dwFlags, *lplpDDPalette);
		if( SUCCEEDED( hResult ) )
		{
			Wrap( This->dd_parent, iid_to_vtbl( IID_IDirectDrawPalette ), (void**)lplpDDPalette );
		}
		EPILOGUE( hResult );
	}

	HRESULT __stdcall CreateSurface( WRAP* This, LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE *lplpDDSurface, IUnknown *pUnkOuter )
	{
		PROLOGUE;
		HRESULT hResult;
		INFO("CreateSurface DD %08X dwCaps %08X\n", This->dd1, lpDDSurfaceDesc->ddsCaps.dwCaps);
		if (This->dd_parent->enabled) {
			if (lpDDSurfaceDesc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE) {
				bool dual = lpDDSurfaceDesc->ddsCaps.dwCaps & DDSCAPS_COMPLEX;
				if (This->dd_parent->caps) {
					lpDDSurfaceDesc->dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
					lpDDSurfaceDesc->dwBackBufferCount = 1; // We only support 1 back buffer yet.
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
				} else {
					lpDDSurfaceDesc->dwFlags = DDSD_CAPS;
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
				}
				hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &This->dd_parent->real[0], pUnkOuter);
				if (SUCCEEDED(hResult)) {
					if (This->dd_parent->caps) {
						DDSCAPS ddsCaps = {0};
						ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
						hResult = This->dd_parent->real[0]->lpVtbl->GetAttachedSurface(This->dd_parent->real[0], &ddsCaps, &This->dd_parent->real[1]);
					} else {
						This->dd_parent->real[1] = NULL;
					}
					INFO("  realFront: %08X, realBack: %08X\n", This->dd_parent->real[0], This->dd_parent->real[1]);

					if (dx::NoBuffer) {
						This->dd_parent->buffer = NULL;
					} else {
						lpDDSurfaceDesc->dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
						lpDDSurfaceDesc->dwHeight = This->dd_parent->height;
						lpDDSurfaceDesc->dwWidth = This->dd_parent->width;
						lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
						hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &This->dd_parent->buffer, pUnkOuter);
						INFO("  buffer: %08X\n", This->dd_parent->buffer);
					}

					lpDDSurfaceDesc->dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS | DDSD_PIXELFORMAT;
					lpDDSurfaceDesc->dwHeight = This->dd_parent->height;
					lpDDSurfaceDesc->dwWidth = This->dd_parent->width;
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
					lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
					lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = This->dd_parent->bpp == 8 ? DDPF_RGB | DDPF_PALETTEINDEXED8 : DDPF_RGB;
					lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = This->dd_parent->bpp;
					lpDDSurfaceDesc->ddpfPixelFormat.dwRBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0xF800 : 0xFF0000);
					lpDDSurfaceDesc->ddpfPixelFormat.dwGBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x07E0 : 0x00FF00);
					lpDDSurfaceDesc->ddpfPixelFormat.dwBBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x001F : 0x0000FF);
					lpDDSurfaceDesc->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
					if (SUCCEEDED(hResult) && dual) {
						hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &This->dd_parent->fake[1], pUnkOuter);
						*lplpDDSurface = This->dd_parent->fake[1];
						Wrap(This->dd_parent, dd_to_dds_vtbl(This), (void**)lplpDDSurface);
					} else {
						This->dd_parent->fake[1] = NULL;
					}
					if (SUCCEEDED(hResult)) hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &This->dd_parent->fake[0], pUnkOuter);
					*lplpDDSurface = This->dd_parent->fake[0];
					INFO("  fakeFront: %08X, fakeBack: %08X\n", This->dd_parent->fake[0], This->dd_parent->fake[1]);
				}
			} else {
				lpDDSurfaceDesc->dwFlags |= DDSD_CAPS | DDSD_PIXELFORMAT;
				lpDDSurfaceDesc->ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
				lpDDSurfaceDesc->ddsCaps.dwCaps &= ~DDSCAPS_VIDEOMEMORY;
				lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
				lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = This->dd_parent->bpp == 8 ? DDPF_RGB | DDPF_PALETTEINDEXED8 : DDPF_RGB;
				lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = This->dd_parent->bpp;
				lpDDSurfaceDesc->ddpfPixelFormat.dwRBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0xF800 : 0xFF0000);
				lpDDSurfaceDesc->ddpfPixelFormat.dwGBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x07E0 : 0x00FF00);
				lpDDSurfaceDesc->ddpfPixelFormat.dwBBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x001F : 0x0000FF);
				lpDDSurfaceDesc->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
				hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, lplpDDSurface, pUnkOuter);
				if (SUCCEEDED(hResult) && This->dd_parent->palette) (*lplpDDSurface)->lpVtbl->SetPalette(*lplpDDSurface, This->dd_parent->palette);
				INFO("  offScreen %08X\n", *lplpDDSurface);
			}
		} else {
			hResult = This->dd1->lpVtbl->CreateSurface( This->dd1, lpDDSurfaceDesc, lplpDDSurface, pUnkOuter );
		}
		if( SUCCEEDED( hResult ) )
		{
			Wrap( This->dd_parent, dd_to_dds_vtbl( This ), (void**)lplpDDSurface );
		}
		EPILOGUE( hResult );
	}

	HRESULT __stdcall DuplicateSurface( WRAP* This, LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE *lplpDupDDSurface )
	{
		PROLOGUE;
		lpDDSurface = GetInnerInterface(lpDDSurface);
		HRESULT hResult = This->dd1->lpVtbl->DuplicateSurface(This->dd1, lpDDSurface, lplpDupDDSurface);
		INFO("DuplicateSurface %08X -> %08X\n", lpDDSurface, *lplpDupDDSurface);
		if( SUCCEEDED( hResult ) ) Wrap( This->dd_parent, dd_to_dds_vtbl( This ), (void**)lplpDupDDSurface );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall EnumDisplayModes( WRAP* This, DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->EnumDisplayModes( This->dd1, dwFlags, lpDDSurfaceDesc, lpContext, lpEnumModesCallback );
		INFO("EnumDisplayModes dwFlags %08X desc %08X callback %08X\n", dwFlags, lpDDSurfaceDesc, lpEnumModesCallback);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall EnumSurfaces( WRAP* This, DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback )
	{
		PROLOGUE;
		EnumStruct e;
		e.callback = (void*)lpEnumSurfacesCallback;
		e.context = lpContext;
		e.dd_parent = This->dd_parent;
		e.xVtbl = dd_to_dds_vtbl( This );
		e.must_exist = ( dwFlags & DDENUMSURFACES_DOESEXIST ) ? true : false;
		HRESULT hResult = This->dd1->lpVtbl->EnumSurfaces( This->dd1, dwFlags, lpDDSD, &e, &WrapEnumSurfacesCallback );
		INFO("EnumSurfaces dwFlags %08X desc %08X callback %08X\n", dwFlags, lpDDSD, lpEnumSurfacesCallback);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall FlipToGDISurface( WRAP* This )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->FlipToGDISurface( This->dd1 );
		INFO("FlipToGDISurface DD %08X\n", This->dd1);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetCaps( WRAP* This, LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetCaps( This->dd1, lpDDDriverCaps, lpDDHELCaps );
		INFO("GetCaps DD %08X DRV %08X HEL %08X\n", This->dd1, lpDDDriverCaps, lpDDHELCaps);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetDisplayMode( WRAP* This, LPDDSURFACEDESC lpDDSurfaceDesc )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetDisplayMode( This->dd1, lpDDSurfaceDesc );
		if (This->dd_parent->enabled && (lpDDSurfaceDesc->dwFlags & DDSD_PIXELFORMAT)) {
			lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
			lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = This->dd_parent->bpp == 8 ? DDPF_RGB | DDPF_PALETTEINDEXED8 : DDPF_RGB;
			lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = This->dd_parent->bpp;
			lpDDSurfaceDesc->ddpfPixelFormat.dwRBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0xF800 : 0xFF0000);
			lpDDSurfaceDesc->ddpfPixelFormat.dwGBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x07E0 : 0x00FF00);
			lpDDSurfaceDesc->ddpfPixelFormat.dwBBitMask = This->dd_parent->bpp == 8 ? 0 : (This->dd_parent->bpp == 16 ? 0x001F : 0x0000FF);
			lpDDSurfaceDesc->ddpfPixelFormat.dwRGBAlphaBitMask = 0;
		}
		// TODO: May need to fix lPitch too.
		INFO("GetDisplayMode DD %08X\n", This->dd1);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetFourCCCodes( WRAP* This, LPDWORD lpNumCodes, LPDWORD lpCodes )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetFourCCCodes( This->dd1, lpNumCodes, lpCodes );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetGDISurface( WRAP* This, LPDIRECTDRAWSURFACE *lplpGDIDDSurface )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetGDISurface( This->dd1, lplpGDIDDSurface );
		INFO("GetGDISurface -> %08X\n", *lplpGDIDDSurface);
		// On modern Windows, GDI surface is exactly the primary DDRAW surface. WTF?!
		if (This->dd_parent->enabled) {
			This->dd_parent->gdi = *lplpGDIDDSurface;
			INFO("  GDI surface is set\n");
		}
		if( SUCCEEDED( hResult ) ) Wrap( This->dd_parent, dd_to_dds_vtbl( This ), (void**)lplpGDIDDSurface );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetMonitorFrequency( WRAP* This, LPDWORD lpdwFrequency )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetMonitorFrequency( This->dd1, lpdwFrequency );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetScanLine( WRAP* This, LPDWORD lpdwScanLine )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetScanLine( This->dd1, lpdwScanLine );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetVerticalBlankStatus( WRAP* This, BOOL *lpbIsInVB )
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetVerticalBlankStatus( This->dd1, lpbIsInVB );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall Initialize( WRAP* This, GUID *lpGUID )
	{ 		
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->Initialize( This->dd1, lpGUID );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall RestoreDisplayMode( WRAP* This )
	{
		PROLOGUE;
		INFO("RestoreDisplayMode DD %08X\n", This->dd1);
		HRESULT hResult = This->dd1->lpVtbl->RestoreDisplayMode( This->dd1 );
		if (This->dd_parent->enabled) {
			This->dd_parent->caps = 0;
			This->dd_parent->width = GetSystemMetrics(SM_CXSCREEN);
			This->dd_parent->height = GetSystemMetrics(SM_CYSCREEN);
			INFO("  restored %d x %d x %d\n", This->dd_parent->width, This->dd_parent->height, This->dd_parent->bpp);
		}
		EPILOGUE( hResult );
	}

	HRESULT __stdcall SetCooperativeLevel( WRAP* This, HWND hWnd, DWORD dwFlags )
	{ 		
		PROLOGUE;
		INFO("SetCooperativeLevel DD %08X dwFlags %08X\n", This->dd1, dwFlags);
		if (dx::UseFlip && (dwFlags & DDSCL_FULLSCREEN)) {
			DDCAPS ddcaps = {0};
			ddcaps.dwSize = sizeof(ddcaps);
			This->dd1->lpVtbl->GetCaps(This->dd1, &ddcaps, NULL);
			if (ddcaps.ddsCaps.dwCaps & DDSCAPS_FLIP) This->dd_parent->caps = 1;
			INFO("  DDCAPS.DDSCAPS.DWCAPS %08X dx::caps %d\n", ddcaps.ddsCaps.dwCaps, This->dd_parent->caps);
		} else {
			This->dd_parent->caps = 0;
		}
		if (dx::BPP && (dwFlags & DDSCL_NORMAL)) {
			HDC dc = GetDC(NULL);
			DWORD bpp = GetDeviceCaps(dc, BITSPIXEL) * GetDeviceCaps(dc, PLANES);
			ReleaseDC(NULL, dc);
			if (bpp != dx::BPP) {
				This->dd_parent->enabled = 1;
				This->dd_parent->width = GetSystemMetrics(SM_CXSCREEN);
				This->dd_parent->height = GetSystemMetrics(SM_CYSCREEN);
				This->dd_parent->bpp = dx::BPP;
				INFO("  enabled: %d x %d x %d -> %d\n", This->dd_parent->width, This->dd_parent->height, This->dd_parent->bpp, bpp);
			}
		}
		HRESULT hResult = This->dd1->lpVtbl->SetCooperativeLevel( This->dd1, hWnd, dwFlags );
		EPILOGUE( hResult );
	}

	// The signature of SetDisplayMode is different between v1 and v2
	HRESULT __stdcall SetDisplayMode1( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP )
	{
		PROLOGUE;
		INFO("SetDisplayMode1 DD %08X %d x %d x %d\n", This->dd1, dwWidth, dwHeight, dwBPP);
		HDC dc = GetDC(NULL);
		DWORD bpp = GetDeviceCaps(dc, BITSPIXEL) * GetDeviceCaps(dc, PLANES);
		ReleaseDC(NULL, dc);
		if (bpp != dwBPP) {
			This->dd_parent->enabled = 1;
			This->dd_parent->width = dwWidth;
			This->dd_parent->height = dwHeight;
			This->dd_parent->bpp = dwBPP;
			dwBPP = bpp;
			INFO("  enabled: %d -> %d\n", This->dd_parent->bpp, bpp);
		}
		HRESULT hResult = This->dd1->lpVtbl->SetDisplayMode(This->dd1, dwWidth, dwHeight, dwBPP);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall SetDisplayMode2( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags )
	{
		PROLOGUE;
		INFO("SetDisplayMode2 DD %08X %d x %d x %d\n", This->dd1, dwWidth, dwHeight, dwBPP);
		HDC dc = GetDC(NULL);
		DWORD bpp = GetDeviceCaps(dc, BITSPIXEL) * GetDeviceCaps(dc, PLANES);
		ReleaseDC(NULL, dc);
		if (bpp != dwBPP) {
			This->dd_parent->enabled = 1;
			This->dd_parent->width = dwWidth;
			This->dd_parent->height = dwHeight;
			This->dd_parent->bpp = dwBPP;
			dwBPP = bpp;
			INFO("  enabled: %d -> %d\n", This->dd_parent->bpp, bpp);
		}
		HRESULT hResult = This->dd2->lpVtbl->SetDisplayMode(This->dd2, dwWidth, dwHeight, dwBPP, dwRefreshRate, dwFlags);
		EPILOGUE( hResult );
	}

	HRESULT __stdcall WaitForVerticalBlank( WRAP* This, DWORD dwFlags, HANDLE hEvent)
	{
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->WaitForVerticalBlank( This->dd1, dwFlags, hEvent );
		EPILOGUE( hResult );
	}

	// v2 //

	HRESULT __stdcall GetAvailableVidMem( WRAP* This, LPDDSCAPS lpDDCaps, LPDWORD lpdwTotal, LPDWORD lpdwFree )
	{
		PROLOGUE;
		HRESULT hResult = This->dd2->lpVtbl->GetAvailableVidMem( This->dd2, lpDDCaps, lpdwTotal, lpdwFree );
		EPILOGUE( hResult );
	}

	// v4 //

	HRESULT __stdcall GetSurfaceFromDC( WRAP* This, HDC hdc, LPDIRECTDRAWSURFACE4* lplpDDSurface )
	{
		PROLOGUE;
		HRESULT hResult = This->dd4->lpVtbl->GetSurfaceFromDC( This->dd4, hdc, lplpDDSurface );
		if( SUCCEEDED( hResult ) ) Wrap( This->dd_parent, dd_to_dds_vtbl( This ), (void**)lplpDDSurface );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall RestoreAllSurfaces( WRAP* This )
	{
		PROLOGUE;
		HRESULT hResult = This->dd4->lpVtbl->RestoreAllSurfaces( This->dd4 );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall TestCooperativeLevel( WRAP* This )
	{
		PROLOGUE;
		HRESULT hResult = This->dd4->lpVtbl->TestCooperativeLevel( This->dd4 );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetDeviceIdentifier( WRAP* This, LPDDDEVICEIDENTIFIER pDDDI, DWORD dwFlags )
	{
		PROLOGUE;
		HRESULT hResult = This->dd4->lpVtbl->GetDeviceIdentifier( This->dd4, pDDDI, dwFlags );
		EPILOGUE( hResult );
	}

	// v7 //

	HRESULT __stdcall StartModeTest( WRAP* This, LPSIZE pModes, DWORD dwNumModes, DWORD dwFlags)
	{
		PROLOGUE;
		HRESULT hResult = This->dd7->lpVtbl->StartModeTest( This->dd7, pModes, dwNumModes, dwFlags );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall EvaluateMode( WRAP* This, DWORD dwFlags, DWORD* pTimeout )
	{
		PROLOGUE;
		HRESULT hResult = This->dd7->lpVtbl->EvaluateMode( This->dd7, dwFlags, pTimeout );
		EPILOGUE( hResult );
	}

	const XVTBL xVtbl1 = {
		QueryInterface,         // 0x00
		AddRef,                 // 0x04
		Release,                // 0x08
		Compact,                // 0x0C
		CreateClipper,          // 0x10
		CreatePalette,          // 0x14
		CreateSurface,          // 0x18
		DuplicateSurface,       // 0x1C
		EnumDisplayModes,       // 0x20
		EnumSurfaces,           // 0x24
		FlipToGDISurface,       // 0x28
		GetCaps,                // 0x2C
		GetDisplayMode,         // 0x30
		GetFourCCCodes,         // 0x34
		GetGDISurface,          // 0x38
		GetMonitorFrequency,    // 0x3C
		GetScanLine,            // 0x40
		GetVerticalBlankStatus, // 0x44
		Initialize,             // 0x48
		RestoreDisplayMode,     // 0x4C
		SetCooperativeLevel,    // 0x50
		(void*)SetDisplayMode1, // 0x54
		WaitForVerticalBlank,   // 0x58
		0, // 0x5C
		0, // 0x60
		0, // 0x64
		0, // 0x68
		0, // 0x6C
		0, // 0x70
		0, // 0x74
	};

	const XVTBL xVtbl2 = {
		QueryInterface,         // 0x00
		AddRef,                 // 0x04
		Release,                // 0x08
		Compact,                // 0x0C
		CreateClipper,          // 0x10
		CreatePalette,          // 0x14
		CreateSurface,          // 0x18
		DuplicateSurface,       // 0x1C
		EnumDisplayModes,       // 0x20
		EnumSurfaces,           // 0x24
		FlipToGDISurface,       // 0x28
		GetCaps,                // 0x2C
		GetDisplayMode,         // 0x30
		GetFourCCCodes,         // 0x34
		GetGDISurface,          // 0x38
		GetMonitorFrequency,    // 0x3C
		GetScanLine,            // 0x40
		GetVerticalBlankStatus, // 0x44
		Initialize,             // 0x48
		RestoreDisplayMode,     // 0x4C
		SetCooperativeLevel,    // 0x50
		(void*)SetDisplayMode2, // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		0, // 0x60
		0, // 0x64
		0, // 0x68
		0, // 0x6C
		0, // 0x70
		0,  // 0x74
	};

	const XVTBL xVtbl4 = {
		QueryInterface,         // 0x00
		AddRef,                 // 0x04
		Release,                // 0x08
		Compact,                // 0x0C
		CreateClipper,          // 0x10
		CreatePalette,          // 0x14
		CreateSurface,          // 0x18
		DuplicateSurface,       // 0x1C
		EnumDisplayModes,       // 0x20
		EnumSurfaces,           // 0x24
		FlipToGDISurface,       // 0x28
		GetCaps,                // 0x2C
		GetDisplayMode,         // 0x30
		GetFourCCCodes,         // 0x34
		GetGDISurface,          // 0x38
		GetMonitorFrequency,    // 0x3C
		GetScanLine,            // 0x40
		GetVerticalBlankStatus, // 0x44
		Initialize,             // 0x48
		RestoreDisplayMode,     // 0x4C
		SetCooperativeLevel,    // 0x50
		(void*)SetDisplayMode2, // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		GetSurfaceFromDC,       // 0x60
		RestoreAllSurfaces,     // 0x64
		TestCooperativeLevel,   // 0x68
		GetDeviceIdentifier,    // 0x6C
		0, // 0x70
		0, // 0x74
	};

	const XVTBL xVtbl7 = {
		QueryInterface,         // 0x00
		AddRef,                 // 0x04
		Release,                // 0x08
		Compact,                // 0x0C
		CreateClipper,          // 0x10
		CreatePalette,          // 0x14
		CreateSurface,          // 0x18
		DuplicateSurface,       // 0x1C
		EnumDisplayModes,       // 0x20
		EnumSurfaces,           // 0x24
		FlipToGDISurface,       // 0x28
		GetCaps,                // 0x2C
		GetDisplayMode,         // 0x30
		GetFourCCCodes,         // 0x34
		GetGDISurface,          // 0x38
		GetMonitorFrequency,    // 0x3C
		GetScanLine,            // 0x40
		GetVerticalBlankStatus, // 0x44
		Initialize,             // 0x48
		RestoreDisplayMode,     // 0x4C
		SetCooperativeLevel,    // 0x50
		(void*)SetDisplayMode2, // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		GetSurfaceFromDC,       // 0x60
		RestoreAllSurfaces,     // 0x64
		TestCooperativeLevel,   // 0x68
		GetDeviceIdentifier,    // 0x6C
		StartModeTest,          // 0x70
		EvaluateMode,           // 0x74
	};
};
