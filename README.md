# pal-ddraw DirectDraw Palette Emulator

pal-ddraw is a wrapper of "ddraw.dll", which is used by many games and programs to render 2D graphics.

pal-ddraw aims to support DirectDraw legacy 8-bit (256 colors) palette mode across both legacy and modern Windows versions when running in 16/24/32 bit color mode. 

pal-ddraw emulates DirectDraw legacy 8-bit (256 colors) palette mode by falling back to GDI, which guaratees it can run natively with Win95/98/2K/Me/XP/Vista/7/8/10 both on real machines and virtual machines. 

# Why:

Many old games and programs were specifically designed to run only in DirectDraw 8-bit (256 colors) palette mode. 
Unfotunately both Windows and DirectDraw have dropped the support to legacy 8-bit color mode which requires a palette.
These games and programs simply fail to run properly when Windows destop is set to 16/24/32 bit color mode.
In many cases, changing the compatibility settting to 8-bit (256) color mode does not help at all because of DirectDraw.
Even worse, they could also fail to run in virtual machines with a legacy OS like Win95/98/XP installled due to virtual driver issues.
In such cases, pal-ddraw may help you, especially when you need to run on a legacy OS where Direct3D or OpenGL2 is not available.

# Usage:

1. Make sure the game is indeed designed to run only in DirectDraw 8-bit (256 colors) palette mode.

Tip: If the game is not utilizing DirectDraw 8-bit (256 colors) palette mode, then you don't need this wrapper.

2. Extract the dll file to the game folder where the game's main executable file is located.

3. Run the game in full screen and enjoy the emulated DirectDraw 8-bit (256 colors) palette mode.

# Notes:

1. I know there are already several other DirectDraw wrappers, but they all forward the rendering to either Direct3D 8/9/10 or OpenGL2, which means they won't run on legacy OS like Win95/98/etc. My goal is support all legacy OS on both real machine and virtual machine.

2. Emulating DirectDraw palette by falling back to GDI inevitablly brings some performance lost, but this should be negligible for old games whose native resolution is usually rather low like 640x480 or 800x600.

3. Currently only full screen mode emulation is implemented. Window mode emulation may be implemented later. 

# Building:

- Use MinGW-w64 x86 (32-bit) to build on Windows OS.

# Revisions:

v.2022.04.04:
- Initial support of both Blt and Flip in full screen mode.

