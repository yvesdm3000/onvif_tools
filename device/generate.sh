wsdl2h -O4 -g -c++11 -P -t /usr/share/gsoap/WS/typemap.dat -o ./onvif.h https://www.onvif.org/ver10/device/wsdl/devicemgmt.wsdl
soapcpp2 -I/usr/share/gsoap -CL onvif.h

