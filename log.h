/*
	all hookprocs start with PROLOGUE and end with EPILOGUE(x) macros
	those macros can be redefined for logging...

	internal functions are sprinkled with TRACE macros

	lets say we want to log only failed IDirectDrawClipper calls then
	we'd paste the "log light" section (below) in clipper.cpp after the #include(s)

	if instead we want to log failed calls for all interfaces then
	just uncomment the "log light" section in this header file

	LogDDSD and dds32_to_bmp are currently not used anywhere
	they exist in case someone wants them for debugging
*/

void __cdecl Log( const char* fmt, ... );
void LogDDSD( LPDDSURFACEDESC lpDDSurfaceDesc );
void LogGUID( const GUID& riid );
void dds32_to_bmp( IDirectDrawSurface* pDDSurface, char* szFileName );

#define EPILOGUE(x) return(x)	
#define LOG_GUID(x)
#define PROLOGUE
#define TRACE(x)
#define WARN(x)
#define INFO(...)

/*
// log light ( warnings, failed iface calls, some iface ids )
#undef EPILOGUE
#undef LOG_GUID
#undef WARN
#undef INFO
#define EPILOGUE(x) if(FAILED(x)){Log( "ERROR %08X caller %08X -> %s\n", x, __builtin_return_address(0), __FUNCTION__ );} return(x)
#define LOG_GUID(x) LogGUID( x )
#define WARN(x)     Log( "WARNING: %s\n", x )
#define INFO(...)   Log(__VA_ARGS__)

// log heavy
#undef EPILOGUE
#undef LOG_GUID
#undef PROLOGUE
#undef TRACE
#undef WARN
#undef INFO
#define EPILOGUE(x) Log( "< (%08X) %s\n", x, __FUNCTION__ ); return(x)
#define LOG_GUID(x) LogGUID( x )
#define PROLOGUE    Log( "> caller %08X -> %s\n", __builtin_return_address(0), __FUNCTION__ )
#define TRACE(x)    Log( "TRACE: %s %s\n", __FUNCTION__, x )
#define WARN(x)     Log( "WARNING: %s %s\n", __FUNCTION__, x )
#define INFO(...)   Log(__VA_ARGS__)
*/
