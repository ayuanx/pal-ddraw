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
		if (dx::enabled) {
			if (lpDDSurfaceDesc->ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE) {
				if (dx::caps) {
					lpDDSurfaceDesc->dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
					lpDDSurfaceDesc->dwBackBufferCount = 1;
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
				} else {
					lpDDSurfaceDesc->dwFlags = DDSD_CAPS;
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
				}
				hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &dx::real[0], pUnkOuter);
				if (SUCCEEDED(hResult)) {
					if (dx::caps) {
						DDSCAPS ddsCaps = {0};
						ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
						hResult = dx::real[0]->lpVtbl->GetAttachedSurface(dx::real[0], &ddsCaps, &dx::real[1]);
					}
					INFO("realFront: %08X, realBack: %08X\n", dx::real[0], dx::real[1]);

					if (!dx::NoBuffer) {
						lpDDSurfaceDesc->dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
						lpDDSurfaceDesc->dwHeight = dx::height;
						lpDDSurfaceDesc->dwWidth = dx::width;
						lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
						hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &dx::buffer, pUnkOuter);
						INFO("buffer: %08X\n", dx::buffer);
					}

					lpDDSurfaceDesc->dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS | DDSD_PIXELFORMAT;
					lpDDSurfaceDesc->dwHeight = dx::height;
					lpDDSurfaceDesc->dwWidth = dx::width;
					lpDDSurfaceDesc->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
					lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
					lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED8;
					lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = 8;
					if (SUCCEEDED(hResult)) hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &dx::fake[1], pUnkOuter);
					*lplpDDSurface = dx::fake[1];
					Wrap(This->dd_parent, dd_to_dds_vtbl(This), (void**)lplpDDSurface);
					if (SUCCEEDED(hResult)) hResult = This->dd1->lpVtbl->CreateSurface(This->dd1, lpDDSurfaceDesc, &dx::fake[0], pUnkOuter);
					*lplpDDSurface = dx::fake[0];
					INFO("fakeFront: %08X, fakeBack: %08X\n", dx::fake[0], dx::fake[1]);
				}
			} else {
				lpDDSurfaceDesc->dwFlags |= DDSD_CAPS | DDSD_PIXELFORMAT;
				lpDDSurfaceDesc->ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
				lpDDSurfaceDesc->ddsCaps.dwCaps &= ~DDSCAPS_VIDEOMEMORY;
				lpDDSurfaceDesc->ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
				lpDDSurfaceDesc->ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED8;
				lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount = 8;
				hResult = This->dd1->lpVtbl->CreateSurface( This->dd1, lpDDSurfaceDesc, lplpDDSurface, pUnkOuter );
				INFO("CreateSurface %08X\n", *lplpDDSurface);
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
		EPILOGUE( hResult );
	}

	HRESULT __stdcall FlipToGDISurface( WRAP* This ) 
	{ 
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->FlipToGDISurface( This->dd1 );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetCaps( WRAP* This, LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps ) 
	{ 
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetCaps( This->dd1, lpDDDriverCaps, lpDDHELCaps );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall GetDisplayMode( WRAP* This, LPDDSURFACEDESC lpDDSurfaceDesc ) 
	{ 
		PROLOGUE;
		HRESULT hResult = This->dd1->lpVtbl->GetDisplayMode( This->dd1, lpDDSurfaceDesc );
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
		INFO("GetGDISurface %08X\n", *lplpGDIDDSurface);
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
		HRESULT hResult = This->dd1->lpVtbl->RestoreDisplayMode( This->dd1 );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall SetCooperativeLevel( WRAP* This, HWND hWnd, DWORD dwFlags ) 
	{ 		
		PROLOGUE;
		if (dx::NoFlip) dx::caps = 0;
		else {
			DDCAPS ddcaps = {0};
			ddcaps.dwSize = sizeof(ddcaps);
			This->dd1->lpVtbl->GetCaps(This->dd1, &ddcaps, NULL);
			if (ddcaps.ddsCaps.dwCaps & DDSCAPS_FLIP) dx::caps = 0;
			INFO("DDCAPS.DDSCAPS.DWCAPS %08X %d\n", ddcaps.ddsCaps.dwCaps, dx::caps);
		}
		HRESULT hResult = This->dd1->lpVtbl->SetCooperativeLevel( This->dd1, hWnd, dwFlags );
		EPILOGUE( hResult );
	}

	// The signature of SetDisplayMode is different between v1 and v2
	HRESULT __stdcall SetDisplayMode1( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP ) 
	{ 
		PROLOGUE;
		if (dwBPP == 8) {
			HDC dc = GetDC(NULL);
			dwBPP = GetDeviceCaps(dc, BITSPIXEL) * GetDeviceCaps(dc, PLANES);
			if (dwBPP != 8) {
				dx::enabled = 1;
				dx::width = dwWidth;
				dx::height = dwHeight;
				INFO("enabled: %d x %d x %d\n", dwWidth, dwHeight, dwBPP);
			}
		}
		HRESULT hResult = This->dd1->lpVtbl->SetDisplayMode( This->dd1, dwWidth, dwHeight, dwBPP );
		EPILOGUE( hResult );
	}

	HRESULT __stdcall SetDisplayMode2( WRAP* This, DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags ) 
	{ 
		PROLOGUE;
		if (dwBPP == 8) {
			HDC dc = GetDC(NULL);
			dwBPP = GetDeviceCaps(dc, BITSPIXEL) * GetDeviceCaps(dc, PLANES);
			if (dwBPP != 8) {
				dx::enabled = 1;
				dx::width = dwWidth;
				dx::height = dwHeight;
				INFO("enabled: %d x %d x %d\n", dwWidth, dwHeight, dwBPP);
			}
		}
		HRESULT hResult = This->dd2->lpVtbl->SetDisplayMode( This->dd2, dwWidth, dwHeight, dwBPP, dwRefreshRate, dwFlags );
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
		(void*)SetDisplayMode1,        // 0x54
		WaitForVerticalBlank,   // 0x58
		0, // 0x5C
		0, // 0x60
		0, // 0x64
		0, // 0x68
		0, // 0x6C
		0, // 0x70
		0  // 0x74
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
		(void*)SetDisplayMode2,        // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		0, // 0x60
		0, // 0x64
		0, // 0x68
		0, // 0x6C
		0, // 0x70
		0  // 0x74
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
		(void*)SetDisplayMode2,        // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		GetSurfaceFromDC,       // 0x60
		RestoreAllSurfaces,     // 0x64
		TestCooperativeLevel,   // 0x68
		GetDeviceIdentifier,    // 0x6C
		0, // 0x70
		0  // 0x74
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
		(void*)SetDisplayMode2,        // 0x54
		WaitForVerticalBlank,   // 0x58
		GetAvailableVidMem,     // 0x5C
		GetSurfaceFromDC,       // 0x60
		RestoreAllSurfaces,     // 0x64
		TestCooperativeLevel,   // 0x68
		GetDeviceIdentifier,    // 0x6C
		StartModeTest,          // 0x70
		EvaluateMode            // 0x74
	};
};
