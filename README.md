# pal-ddraw DirectDraw Palette & Color Depth Emulator

pal-ddraw is a wrapper of DirectDraw (ddraw.dll), which is used by many games and programs to render 2D graphics.

pal-ddraw can emulate all color depths of DirectDraw (i.e. 8-bit/16-bit/24-bit/32-bit color depth) across all legacy and modern Windows versions, even when the real DirectDraw on your Windows does not provide or support such color depths.

Particularly, pal-draw can emulate DirectDraw legacy 8-bit color depth (256 colors) that requires a palette, when modern Windows only works in 32-bit color depth and does not provide options to switch color depth anymore.

pal-ddraw emulates DirectDraw 8-bit/16-bit/24-bit/32-bit color depth by falling back to GDI, which guarantees it can run natively with Win95/98/NT/2K/Me/XP/Vista/7/8/10 on both real machines and virtual machines. 

# Why:

Many old games and programs were specifically designed to run in DirectDraw 8-bit or 16-bit color depth mode only.

Unfotunately both Windows and DirectDraw have dropped the support for such legacy color depths like 8-bit or 16-bit.

As a result, these old games and programs fail to run properly when Windows desktop only supports 32-bit color depth.

In many cases, changing the compatibility setttings to 8-bit or 16-bit color depth mode does not help at all because of the involvement of DirectDraw.

Even worse, they could also fail to run in a virtual machine with a legacy OS like Win95/98/XP installled due to virtual display driver issues.

In such cases, pal-ddraw may help you, especially when you need to run on a legacy OS where Direct3D or OpenGL2 is not available.

# Usage:

1. Make sure the game is indeed designed to run in a specific DirectDraw color depth mode (e.g. 8-bit or 16-bit) which your current Windows does not support.

Tip: If the game does not utilize DirectDraw at all, or if the game already supports your current desktop color depth (which is usually 32-bit color depth) natively, then you don't need this wrapper.

2. Extract the dll file and the ini file to the game folder where the game's main executable file is located.

3. (Optional) Change the configuration in "ddraw.ini" file if needed.

4. Run the game in full screen mode and enjoy the DirectDraw color depth emulation.

# Notes:

* I know there are already several other DirectDraw wrappers, but they all forward the rendering to either Direct3D 8/9/10 or OpenGL2/Vulkan, which means they won't run on legacy OS like Win95/98/XP. My goal is support all legacy and modern OSes on both real machines and virtual machines.

* Emulating DirectDraw color depth by falling back to GDI inevitablly incurs some performance loss, but this is generally negligible for old games whose native resolution is usually rather low like 640x480, 800x600, or 1024x768.

* Currently only full screen mode emulation is implemented. Window mode emulation may be implemented later. 

# Building:

- Use MinGW-w64 x86 (32-bit) to build on Windows OS.

# Revisions:

v.2024.08.25
- Fix the crash when one DirectDraw interface is released but several other are still active. 
- Improve compatibility for games that utilize undocumented DDThreadLock methods.

v.2024.08.04
- Compatibility fix for GetDisplayMode.

v.2023.08.04
- Export DirectDrawEnumerateExA.

v.2023.06.01
- Extend the color depth emulation from 8-bit to 8-bit/16-bit/24-bit/32-bit.

v.2022.11.21
- Support full screen clipper.
- Proper release of palette.
- Proper handling of DDERR_SURFACELOST.
- Change throttle to 60 FPS.

v.2022.05.07
- Various compatibility fix.

v.2022.04.07
- Configurable flip, buffer and throttle.
- Improve performance.
- Improve compatibility.
- Proper release sequence.
- Bug fixes.

v.2022.04.04
- Initial support of both Blt and Flip in full screen mode.

