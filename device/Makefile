
all:
	g++ -std=c++11 `pkg-config --cflags gsoap++` -I. main.cpp soapDeviceBindingProxy.cpp soapC.cpp  /usr/share/gsoap/custom/duration.c  `pkg-config --libs gsoap++`  -o onvif_device_tool
