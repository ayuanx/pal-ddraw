# pal-ddraw DirectDraw Palette Emulator

pal-ddraw is a wrapper of "ddraw.dll", which is used by many games and programs to render 2D graphics.

pal-ddraw aims to support DirectDraw legacy 8-bit (256 colors) palette mode across all legacy and modern Windows versions when running in 16/24/32 bit color mode. 

pal-ddraw emulates DirectDraw legacy 8-bit (256 colors) palette mode by falling back to GDI, which guarantees it can run natively with Win95/98/NT/2K/Me/XP/Vista/7/8/10 on both real machines and virtual machines. 

# Why:

Many old games and programs were specifically designed to run in DirectDraw 8-bit (256 colors) palette mode only.

Unfotunately both Windows and DirectDraw have dropped the support for legacy 8-bit color mode that requires a palette.

As a result, these old games and programs fail to run properly when Windows desktop is set to 16/24/32 bit color mode.

In many cases, changing the compatibility setttings to 8-bit (256) color mode does not help at all because of DirectDraw.

Even worse, they could also fail to run in a virtual machine with a legacy OS like Win95/98/XP installled due to virtual driver issues.

In such cases, pal-ddraw may help you, especially when you need to run on a legacy OS where Direct3D or OpenGL2 is not available.

# Usage:

1. Make sure the game is indeed designed to run in DirectDraw 8-bit (256 colors) palette mode only.

Tip: If the game is not utilizing DirectDraw 8-bit (256 colors) palette mode, then you don't need this wrapper.

2. Extract the dll file and the ini file to the game folder where the game's main executable file is located.

3. (Optional) Change the configuration in "ddraw.ini" file if needed.

4. Run the game in full screen mode and enjoy the DirectDraw 8-bit (256 colors) palette emulation.

# Notes:

* I know there are already several other DirectDraw wrappers, but they all forward the rendering to either Direct3D 8/9/10 or OpenGL2/Vulkan, which means they won't run on legacy OS like Win95/98/XP. My goal is support all legacy and modern OSes on both real machine and virtual machine.

* Emulating DirectDraw palette by falling back to GDI inevitablly incurs some performance lost, but this should be negligible for old games whose native resolution is usually rather low like 640x480 or 800x600 and does not require a high refresh rate.

* Currently only full screen mode emulation is implemented. Window mode emulation may be implemented later. 

# Building:

- Use MinGW-w64 x86 (32-bit) to build on Windows OS.

# Revisions:

v.2022.11.19:
- Proper handling of DDERR_SURFACELOST.
- Change throttle to 60 FPS.

v.2022.05.07:
- Various compatibility fix.

v.2022.04.07:
- Configurable flip, buffer and throttle.
- Improve performance.
- Improve compatibility.
- Proper release sequence.
- Bug fixes.

v.2022.04.04:
- Initial support of both Blt and Flip in full screen mode.

