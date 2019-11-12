#include "DeviceBinding.nsmap"
#include "soapDeviceBindingProxy.h"
#include <stdio.h>

void cmd_syncTime( DeviceBindingProxy& proxy )
{
    _tds__GetSystemDateAndTime g;
    _tds__GetSystemDateAndTimeResponse response;
    int ret = proxy.GetSystemDateAndTime( &g, response );
    if (ret == 0)
    {
      int tp = (int)response.SystemDateAndTime->DateTimeType;
      printf("type: %d\n", tp);
      printf("%s\n", response.SystemDateAndTime->TimeZone->TZ.c_str());
      if (response.SystemDateAndTime->UTCDateTime) 
      {
        printf("%02d:%02d:%02d\n", response.SystemDateAndTime->UTCDateTime->Time->Hour, response.SystemDateAndTime->UTCDateTime->Time->Minute, response.SystemDateAndTime->UTCDateTime->Time->Second);
      }
      if (response.SystemDateAndTime->LocalDateTime)
      {
        printf("%02d:%02d:%02d\n", response.SystemDateAndTime->LocalDateTime->Time->Hour, response.SystemDateAndTime->LocalDateTime->Time->Minute, response.SystemDateAndTime->LocalDateTime->Time->Second);
        printf("%d/%d/%d\n", response.SystemDateAndTime->LocalDateTime->Date->Year, response.SystemDateAndTime->LocalDateTime->Date->Month, response.SystemDateAndTime->LocalDateTime->Date->Day);
      }
      time_t t = time(NULL);
      struct tm* tm = gmtime(&t);
      printf("hour: %d\n", tm->tm_hour);
      printf("year: %d\n", tm->tm_year);
      tt__Time* soapTime = soap_new_set_tt__Time( proxy.soap, tm->tm_hour, tm->tm_min, tm->tm_sec);
      tt__Date* soapDate = soap_new_set_tt__Date( proxy.soap, 1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday);
      //tt__TimeZone* tz = soap_new_set_tt__TimeZone( proxy.soap, "EET-2EETDST" );
      tt__TimeZone* tz = soap_new_set_tt__TimeZone( proxy.soap, "CET-1CEST" );
      tt__DateTime* dt = soap_new_set_tt__DateTime( proxy.soap, soapTime, soapDate );

      _tds__SetSystemDateAndTime* s = soap_new_set__tds__SetSystemDateAndTime( proxy.soap, tt__SetDateTimeType::Manual, tm->tm_isdst > 0, tz, dt );
      _tds__SetSystemDateAndTimeResponse response2;
      ret = proxy.SetSystemDateAndTime( s, response2 );
      if (ret != 0)
      {
        printf("Setting time failed: Returned %d\n", ret);
      }
    }
}

void printNetworkHost( tt__NetworkHost* host )
{
  printf("    type: %d\n", (int)host->Type);
  if (host->IPv4Address)
  {
    printf("    IPV4Address: %s\n", host->IPv4Address->c_str());
  }
  if (host->IPv6Address)
  {
    printf("    IPV6Address: %s\n", host->IPv6Address->c_str());
  }
  if (host->DNSname)
  {
    printf("    DNSname: %s\n", host->DNSname->c_str());
  }
  if (host->Extension)
  {
    printf("    Extension:\n");
    for (auto strPtr : host->Extension->__any)
    {
      printf("      %s\n", strPtr);
    }
  }
}

void cmd_setNTP( DeviceBindingProxy& proxy, const char* ntpServer )
{
  int ret;
  {
    _tds__SetNTP setNTP;
    setNTP.FromDHCP = false;
    tt__NetworkHost host;
    std::string ipv4name = ntpServer;
    host.Type = tt__NetworkHostType::IPv4;
    host.IPv4Address = &ipv4name;
    setNTP.NTPManual.push_back( &host );

    _tds__SetNTPResponse response;
    ret = proxy.SetNTP(&setNTP, response);
    if (ret != 0)
    {
      printf("Set NTP server failed\n");
    }
  }
  {
  _tds__GetNTP getNTP;
  _tds__GetNTPResponse response;

  ret = proxy.GetNTP(&getNTP, response);
  if (ret == 0)
  {
    if (response.NTPInformation)
    {
      printf("  NTP FromDHCP: %d\n", response.NTPInformation->FromDHCP);
      printf("  FromDHCP List:\n");
      for (auto host : response.NTPInformation->NTPFromDHCP)
      {
        printNetworkHost(host);
      }
      printf("  NTPManual:\n");
      for (auto host : response.NTPInformation->NTPManual)
      {
        printNetworkHost(host);
      }
    }
  }
  }
}

int main( int argc, char* argv[] )
{
  int ret;
  if (argc < 2) {
    printf("Usage:\n  %s http://server:8899\n", argv[0]);
    printf("  %s http://server:8899 synctime\n", argv[0]);
    printf("  %s http://server:8899 setntp ntphost\n", argv[0]);
    exit(1);
  }
  DeviceBindingProxy proxy(argv[1]);
  if (argc > 2 ) 
  {
    if (strcmp( argv[2], "synctime") == 0)
    {
      cmd_syncTime( proxy );
      return 0;
    }
  }
  if (argc > 3)
  {
    if (strcmp( argv[2], "setntp") == 0)
    {
      cmd_setNTP( proxy, argv[3] );
      return 0;
    }
  }

  _tds__GetServices getServices;
  _tds__GetServicesResponse getServicesResponse;
  ret = proxy.GetServices( &getServices, getServicesResponse );
  printf("%d\n", ret);
  for( auto& service : getServicesResponse.Service ) 
  {
    printf("namespace: %s\n", service->Namespace.c_str());
    printf("XAddr: %s\n", service->XAddr.c_str());
    printf("Version: %d.%d\n", service->Version->Major, service->Version->Minor);
  }

  _tds__GetDeviceInformation getDeviceInfo;
  _tds__GetDeviceInformationResponse getDeviceInfoResponse;
  ret = proxy.GetDeviceInformation( &getDeviceInfo, getDeviceInfoResponse );
  printf("%d\n", ret);
  printf("Manufacturer: %s\n", getDeviceInfoResponse.Manufacturer.c_str());
  printf("Model: %s\n", getDeviceInfoResponse.Model.c_str());
  printf("FirmwareVersion: %s\n", getDeviceInfoResponse.FirmwareVersion.c_str());
  printf("SerialNumber: %s\n", getDeviceInfoResponse.SerialNumber.c_str());
  printf("HardwareId: %s\n", getDeviceInfoResponse.HardwareId.c_str());

  return 0;
}
