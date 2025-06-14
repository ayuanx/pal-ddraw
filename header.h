#define INITGUID
#define CINTERFACE 

#include <windows.h>
#include <wingdi.h>
#include <ddraw.h>
#include <d3d.h>

#include "wrap.h"
#include "log.h"

extern "C" {
HRESULT __stdcall CompleteCreateSysmemSurface( DWORD arg1 );
HRESULT __stdcall AcquireDDThreadLock();
HRESULT __stdcall ReleaseDDThreadLock();
HRESULT __stdcall DDInternalLock( DWORD arg1, DWORD arg2 );
HRESULT __stdcall DDInternalUnlock( DWORD arg1 );
HRESULT __stdcall D3DParseUnknownCommand( LPVOID lpCmd, LPVOID *lpRetCmd );
}

namespace dd { struct XVTBL; extern const XVTBL xVtbl1; extern const XVTBL xVtbl2; extern const XVTBL xVtbl4; extern const XVTBL xVtbl7; };
namespace dds { struct XVTBL; extern const XVTBL xVtbl1; extern const XVTBL xVtbl2; extern const XVTBL xVtbl3; extern const XVTBL xVtbl4; extern const XVTBL xVtbl7; };
namespace classfactory { struct XVTBL; extern const XVTBL xVtbl; };
namespace clipper { struct XVTBL; extern const XVTBL xVtbl; };
namespace palette { struct XVTBL; extern const XVTBL xVtbl; };
namespace color { struct XVTBL; extern const XVTBL xVtbl; };
namespace gama { struct XVTBL; extern const XVTBL xVtbl; };
namespace unknwn { struct XVTBL; extern const XVTBL xVtbl; };
namespace dx { extern DWORD NoBuffer, UseFlip, UseThrottle, BPP; LPDIRECTDRAWSURFACE MatchFlip(WRAP*, LPDIRECTDRAWSURFACE); HRESULT Stretch(WRAP*, LPDIRECTDRAWSURFACE, LPRECT, LPDIRECTDRAWSURFACE, LPRECT); HRESULT Flush(WRAP*, LPDIRECTDRAWSURFACE, LPRECT = NULL, DWORD = 0, DWORD = DDFLIP_WAIT); };
