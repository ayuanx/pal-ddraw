all: ddraw.dll

ddraw.dll: classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp exports.def dgamma.cpp log.cpp palette.cpp unknwn.cpp wrap.cpp
	gcc -m32 -static-libgcc -Wl,--enable-stdcall-fixup -shared -o ddraw.dll classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp exports.def dgamma.cpp log.cpp palette.cpp unknwn.cpp wrap.cpp -lddraw

clean:
	rm -f ddraw.dll
