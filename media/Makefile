
all:
	g++ -std=c++11 `pkg-config --cflags gsoap++` -I. main.cpp soapMediaBindingProxy.cpp soapC.cpp  /usr/share/gsoap/custom/duration.c  `pkg-config --libs gsoap++`  -o onvif_media_tool
