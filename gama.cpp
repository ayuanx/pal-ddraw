#include "header.h"

namespace gama
{
	struct XVTBL
	{
		HRESULT (__stdcall * QueryInterface)( WRAP* This, const IID& riid, void** ppvObject );
		ULONG   (__stdcall * AddRef)( WRAP* This );
		ULONG   (__stdcall * Release)( WRAP* This );
		HRESULT (__stdcall * GetGammaRamp)( WRAP* This, DWORD dwFlags, LPDDGAMMARAMP lpRampData );
		HRESULT (__stdcall * SetGammaRamp)( WRAP* This, DWORD dwFlags, LPDDGAMMARAMP lpRampData );
	};

	HRESULT __stdcall QueryInterface( WRAP* This, const IID& riid, void** ppvObject )
	{
		PROLOGUE;
		HRESULT hResult = This->gama->lpVtbl->QueryInterface( This->gama, riid, ppvObject );
		if( SUCCEEDED( hResult ) ) Wrap( This->dd_parent, iid_to_vtbl( riid ), ppvObject );
		EPILOGUE( hResult );
	}

	ULONG __stdcall AddRef( WRAP* This )
	{
		PROLOGUE;
		ULONG dwCount = This->gama->lpVtbl->AddRef( This->gama );
		EPILOGUE( dwCount );
	}

	ULONG __stdcall Release( WRAP* This )
	{ 	
		PROLOGUE;
		ULONG dwCount = WrapRelease( This );
		EPILOGUE( dwCount );
	}

	HRESULT __stdcall GetGammaRamp( WRAP* This, DWORD dwFlags, LPDDGAMMARAMP lpRampData )
	{
		PROLOGUE;
		HRESULT hResult = This->gama->lpVtbl->GetGammaRamp( This->gama, dwFlags, lpRampData );
		EPILOGUE( hResult );
	}
	
	HRESULT __stdcall SetGammaRamp( WRAP* This, DWORD dwFlags, LPDDGAMMARAMP lpRampData )
	{
		PROLOGUE;
		HRESULT hResult = This->gama->lpVtbl->SetGammaRamp( This->gama, dwFlags, lpRampData );
		EPILOGUE( hResult );
	}

	const XVTBL xVtbl =
	{
		QueryInterface,    // 0x00
		AddRef,            // 0x04
		Release,           // 0x08
		GetGammaRamp,      // 0x0C
		SetGammaRamp,      // 0x10
	};
};
