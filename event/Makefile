
all:
	g++ `pkg-config --cflags gsoap++` -I. main.cpp soapPullPointSubscriptionBindingProxy.cpp soapC.cpp  /usr/share/gsoap/custom/duration.c  `pkg-config --libs gsoap++`  -o onvif_event_tool
