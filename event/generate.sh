wsdl2h -O0 -g -c++11 -P -t /usr/share/gsoap/WS/typemap.dat -o ./onvif.h https://www.onvif.org/ver10/events/wsdl/event.wsdl
soapcpp2 -I/usr/share/gsoap -j -CL onvif.h

