REV=$(shell sh -c 'date +"%Y,%m,%d"')

all: ddraw.dll

ddraw.rc.o: ddraw.rc.in
	sed 's/__REV__/$(REV)/' ddraw.rc.in | windres -O coff -o ddraw.rc.o

ddraw.dll: classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp gama.cpp dx.cpp header.h log.cpp log.h palette.cpp unknwn.cpp wrap.cpp wrap.h exports.def ddraw.rc.o 
	gcc -m32 -static-libgcc -Wl,--enable-stdcall-fixup -s -O2 -shared -o ddraw.dll classfactory.cpp clipper.cpp color.cpp dd.cpp dds.cpp dllmain.cpp dx.cpp gama.cpp log.cpp palette.cpp unknwn.cpp wrap.cpp exports.def ddraw.rc.o -lddraw -lgdi32

clean:
	rm -f ddraw.dll ddraw.rc.o
