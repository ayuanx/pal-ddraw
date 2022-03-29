REV=$(shell sh -c 'date +"%Y.%m.%d"')

all: ddraw.dll

ddraw.rc.o: ddraw.rc.in
	sed 's/__REV__/$(REV)/' ddraw.rc.in | windres -O coff -o ddraw.rc.o

ddraw.dll: classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp ddraw.rc.o exports.def dgamma.cpp log.cpp palette.cpp unknwn.cpp wrap.cpp
	gcc -m32 -static-libgcc -Wl,--enable-stdcall-fixup -shared -o ddraw.dll classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp ddraw.rc.o exports.def dgamma.cpp log.cpp palette.cpp unknwn.cpp wrap.cpp -lddraw

clean:
	rm -f ddraw.dll
