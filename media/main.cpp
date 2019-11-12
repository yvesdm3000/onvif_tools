#include "MediaBinding.nsmap"
#include "soapMediaBindingProxy.h"
#include <stdio.h>

void printMulticast(const char* label, const tt__MulticastConfiguration *multicast)
{
  printf("%s multicast type: %d\n",label, (int)multicast->Address->Type);
  if (multicast->Address->IPv4Address)
  {
    printf("%s  Address IPv4: %s\n",label, multicast->Address->IPv4Address->c_str());
  }
  if (multicast->Address->IPv6Address)
  {
    printf("%s  Address IPv6: %s\n",label, multicast->Address->IPv6Address->c_str());
  }
  printf("%s  port: %d\n",label, multicast->Port);
  printf("%s  TTL: %d\n",label, multicast->TTL);
  printf("%s  Autostart: %d\n",label, (int)multicast->AutoStart);
}

void printVideoResolution( const char* label, tt__VideoResolution* resolution )
{
  printf("%s: %d : %d\n",label, resolution->Width, resolution->Height);
}

void printConfig(const char* label, tt__Config* config )
{
  printf("%sconfig name: %s\n",label, config->Name.c_str());
  printf("%s  config type: %s\n",label, config->Type.c_str());
  printf("%s  Parameters:\n", label);
  for ( auto& item : config->Parameters->SimpleItem )
  {
    printf("%s    Simple item: %s = %s\n",label, item.Name.c_str(), item.Value.c_str());
  }
  for ( auto& item : config->Parameters->ElementItem )
  {
    printf("%s    Element item: %s\n",label, item.Name.c_str());
    if (item.__any)
    {
      printf("%s      %s\n",label, item.__any);
    }
  }
}

void printMediaUri( tt__MediaUri* uri )
{
  printf("  URI: %s\n", uri->Uri.c_str());
  printf("    Invalid after connect: %d\n", (int)uri->InvalidAfterConnect);
  printf("    Invalid after reboot: %d\n", (int)uri->InvalidAfterReboot);
  printf("    Timeout: %lld\n", uri->Timeout);
}

void cmd_setOSDName( MediaBindingProxy& proxy, const std::string& name )
{
      _trt__GetOSDs getOSDs;
      _trt__GetOSDsResponse getOSDsResponse;
      int ret = proxy.GetOSDs(&getOSDs, getOSDsResponse);
      if (ret == 0)
      {
        printf("OSDs:\n");
        for( auto& osd : getOSDsResponse.OSDs )
        {
          if (osd->TextString)
          {
            if (osd->TextString->Type == "Plain")
            {
              *osd->TextString->PlainText = name;
              _trt__SetOSD setOSD;
              _trt__SetOSDResponse setOSDResponse;
              setOSD.OSD = osd;
              ret = proxy.SetOSD( &setOSD, setOSDResponse );
            }
          }
        }
      }
}

void printMetadataConfiguration( const char* label, tt__MetadataConfiguration* conf )
{
      printf("%sName: %s\n", label, conf->Name.c_str());
      printf("%sUseCount: %d\n", label, conf->UseCount);
      printf("%sToken: %s\n", label, conf->token.c_str());
      if (conf->PTZStatus)
      {
      }
      if (conf->Events)
      {
        if (conf->Events->Filter)
         {
          printf("%sFilter:\n", label);
          for (auto strPtr : conf->Events->Filter->__any)
          {
            printf("%s  %s\n", label, strPtr);
          }
        }
        if (conf->Events->SubscriptionPolicy)
        {
          printf("%sSubscription policy:\n", label);
          for (auto strPtr : conf->Events->SubscriptionPolicy->__any)
          {
            printf("%s  %s\n", label, strPtr);
          }
        }
        for (auto strPtr : conf->Events->__any)
        {
          printf("%s%s\n", label, strPtr);
        }
        if (conf->Events->__anyAttribute)
        {
          printf("%sattr: %s\n", label, conf->Events->__anyAttribute);
        }
      }
      if (conf->Analytics)
      {
        printf("%sAnalytics: %d\n", label, (int)*conf->Analytics);
      }
      if (conf->Multicast)
      {
        printMulticast(label, conf->Multicast );
      }
      printf("%sSession timeout: %lld\n", label, conf->SessionTimeout);
      for (auto strPtr : conf->__any)
      {
        printf("%s%s\n", label, strPtr);
      }
      if (conf->AnalyticsEngineConfiguration)
      {
        printf("%sAnalytics engine configuration:\n", label);
        for (auto& analyticsConf : conf->AnalyticsEngineConfiguration->AnalyticsModule)
        {
          printConfig(label, analyticsConf );
        }
        if (conf->AnalyticsEngineConfiguration->Extension)
        {
          printf("%s  Extension:\n", label);
          for (auto strPtr : conf->AnalyticsEngineConfiguration->Extension->__any)
          {
            printf("%s    %s\n", label, strPtr);
          }
        }
        if (conf->AnalyticsEngineConfiguration->__anyAttribute)
        {
          printf("%s  attr: %s\n", label, conf->AnalyticsEngineConfiguration->__anyAttribute);
        }
      }
      if (conf->Extension)
      {
        printf("%s  extension:\n", label);
        for (auto strPtr : conf->Extension->__any)
        {
          printf("%s    %s\n", label, strPtr);
        }
      }
      if (conf->CompressionType)
      {
        printf("%sCompression Type: %s\n", label, conf->CompressionType->c_str());
      }
      if (conf->GeoLocation)
      {
        printf("%sGeoLocation: %d\n", label, (int)*conf->GeoLocation);
      }
      if (conf->__anyAttribute)
      {
        printf("%sattr: %s\n", label, conf->__anyAttribute);
      }
}
void printMetadataConfigurationOptions( const char* label, tt__MetadataConfigurationOptions* options )
{
    if (options->PTZStatusFilterOptions)
    {
      printf("%sPanTiltStatusSupported: %d\n", label, (int)options->PTZStatusFilterOptions->PanTiltStatusSupported);
      printf("%sZoomStatusSupported: %d\n", label, (int)options->PTZStatusFilterOptions->ZoomStatusSupported);
      for( auto strPtr : options->PTZStatusFilterOptions->__any)
      {
        printf("%s%s\n", label, strPtr);
      }
      if ( options->PTZStatusFilterOptions->PanTiltPositionSupported)
      {
        printf("%sPanTiltPositionSupported: %d\n", label, (int)*options->PTZStatusFilterOptions->PanTiltPositionSupported);
      }
      if (options->PTZStatusFilterOptions->ZoomPositionSupported)
      {
        printf("%sZoomPositionSupported: %d\n", label, (int)*options->PTZStatusFilterOptions->ZoomPositionSupported);
      }
      if (options->PTZStatusFilterOptions->Extension)
      {
        printf("%sExtension:\n", label);
        for (auto strPtr : options->PTZStatusFilterOptions->Extension->__any)
        {
          printf("%s  %s\n", label, strPtr);
        }
      }
      if (options->PTZStatusFilterOptions->__anyAttribute)
      {
        printf("%sattr: %s\n", label, options->PTZStatusFilterOptions->__anyAttribute);
      }
    }
    for (auto strPtr : options->__any)
    {
      printf("%s%s\n", label, strPtr);
    }
    if (options->Extension)
    {
      printf("%sExtension:\n", label);
      printf("%s  Compression Types:\n", label);
      for (auto str : options->Extension->CompressionType)
      {
        printf("%s    %s\n", label, str.c_str());
      }
      for (auto strPtr : options->Extension->Extension->__any)
      {
        printf("%s  %s\n", label, strPtr);
      }
    }
    if (options->GeoLocation)
    {
      printf("%sGeoLocation: %d\n", label, (int)*options->GeoLocation);
    }
}

void cmd_startMulticast( MediaBindingProxy& proxy, const std::string& profileToken )
{
  _trt__StartMulticastStreaming startMulticast;
  startMulticast.ProfileToken = profileToken;
  _trt__StartMulticastStreamingResponse startMulticastResponse;
  int ret = proxy.StartMulticastStreaming(&startMulticast, startMulticastResponse);
  if (ret != 0)
  {
    printf("Starting multicast failed!\n");
    return;
  }
  printf("Multicast started\n");
}

int main( int argc, char* argv[] )
{
  int ret;
  if (argc < 2) {
    printf("Usage:\n  %s http://server:8899\n", argv[0]);
    printf("  %s http://server:8899 setosdname CHANNELNAME\n", argv[0]);
    printf("  %s http://server:8899 startmulticast PROFILETOKEN\n", argv[0]);
    exit(1);
  }

  MediaBindingProxy proxy(argv[1]);

  if (argc >= 4)
  {
    if ( strcmp(argv[2],"setosdname") == 0)
    {
      cmd_setOSDName( proxy, argv[3] );
    }
    else if (strcmp(argv[2],"startmulticast") == 0)
    {
      cmd_startMulticast( proxy, argv[3] );
    }
  }


  _trt__GetServiceCapabilities getServiceCaps;
  _trt__GetServiceCapabilitiesResponse getServiceCapsResponse;
  ret = proxy.GetServiceCapabilities( &getServiceCaps, getServiceCapsResponse );
  if (ret == 0)
  {
    printf("CAPABILITIES:\n");
    printf("  PROFILE CAPABILITIES:\n");
    for (auto strPtr : getServiceCapsResponse.Capabilities->ProfileCapabilities->__any) {
      printf("    %s\n", strPtr);
    }
    if (getServiceCapsResponse.Capabilities->ProfileCapabilities->MaximumNumberOfProfiles) {
      printf("    Maximum capabilities: %d\n", *getServiceCapsResponse.Capabilities->ProfileCapabilities->MaximumNumberOfProfiles);
    }
    if (getServiceCapsResponse.Capabilities->ProfileCapabilities->__anyAttribute) {
      printf("    attr: %s\n", getServiceCapsResponse.Capabilities->ProfileCapabilities->__anyAttribute);
    }
    printf("  STREAMING CAPABILITIES:\n");
    for (auto strPtr : getServiceCapsResponse.Capabilities->StreamingCapabilities->__any) {
      printf("    %s\n", strPtr);
    }
    if (getServiceCapsResponse.Capabilities->StreamingCapabilities->RTPMulticast) {
      printf("    RTPMulticast: %d\n", *getServiceCapsResponse.Capabilities->StreamingCapabilities->RTPMulticast);
    }
    if (getServiceCapsResponse.Capabilities->StreamingCapabilities->RTP_USCORETCP) {
      printf("    RTP_USCORETCP: %d\n", *getServiceCapsResponse.Capabilities->StreamingCapabilities->RTP_USCORETCP);
    }
    if (getServiceCapsResponse.Capabilities->StreamingCapabilities->RTP_USCORERTSP_USCORETCP) {
      printf("    RTP_USCORERTSP_USCORETCP: %d\n", *getServiceCapsResponse.Capabilities->StreamingCapabilities->RTP_USCORERTSP_USCORETCP);
    }
    if (getServiceCapsResponse.Capabilities->StreamingCapabilities->NonAggregateControl) {
      printf("    NonAggregateControl: %d\n", *getServiceCapsResponse.Capabilities->StreamingCapabilities->NonAggregateControl);
    }
    if (getServiceCapsResponse.Capabilities->StreamingCapabilities->NoRTSPStreaming) {
      printf("    NoRTSPStreaming: %d\n", *getServiceCapsResponse.Capabilities->StreamingCapabilities->NoRTSPStreaming);
    }
    for (auto strPtr : getServiceCapsResponse.Capabilities->__any) {
      printf("  %s\n", strPtr);
    }

    if (getServiceCapsResponse.Capabilities->SnapshotUri) {
      printf("  SnapshotUri: %d\n", (int)*getServiceCapsResponse.Capabilities->SnapshotUri);
    }
    if (getServiceCapsResponse.Capabilities->Rotation) {
      printf("  Rotation: %d\n", (int)*getServiceCapsResponse.Capabilities->Rotation);
    }
    if (getServiceCapsResponse.Capabilities->VideoSourceMode) {
      printf("  VideoSourceMode: %d\n", (int)*getServiceCapsResponse.Capabilities->VideoSourceMode);
    }
    if (getServiceCapsResponse.Capabilities->OSD) {
      printf("  OSD: %d\n", (int)*getServiceCapsResponse.Capabilities->OSD);
    }
    if (getServiceCapsResponse.Capabilities->TemporaryOSDText) {
      printf("  TemporaryOSDText: %d\n", (int)*getServiceCapsResponse.Capabilities->TemporaryOSDText);
    }
    if (getServiceCapsResponse.Capabilities->EXICompression) {
      printf("  EXICompression: %d\n", (int)*getServiceCapsResponse.Capabilities->EXICompression);
    }
    if (getServiceCapsResponse.Capabilities->__anyAttribute) {
      printf("  attr: %s\n", getServiceCapsResponse.Capabilities->__anyAttribute);
    }
  }

  _trt__GetVideoSources getVideoSources;
  _trt__GetVideoSourcesResponse getVideoSourcesResponse;
  ret = proxy.GetVideoSources(&getVideoSources, getVideoSourcesResponse);
  if (ret == 0)
  {
    printf("  Video sources:\n");
    for( auto videoSource : getVideoSourcesResponse.VideoSources )
    {
      printf("    token: %s\n", videoSource->token.c_str());
      printf("    Framerate: %f\n", videoSource->Framerate);
      printVideoResolution("    Video resolution:", videoSource->Resolution );
      if (videoSource->Imaging)
      {
        printf("    Imaging:\n");
        if ( videoSource->Imaging->BacklightCompensation )
        {
                printf("      Backlight compensation Mode: %d\n", (int)videoSource->Imaging->BacklightCompensation->Mode);
                printf("      Backlight compensation Level: %f\n", videoSource->Imaging->BacklightCompensation->Level);
        }
        if (videoSource->Imaging->Brightness)
        {
                printf("      Brightness: %f\n", *videoSource->Imaging->Brightness);
        }
        if (videoSource->Imaging->ColorSaturation)
        {
                printf("      Color Saturation: %f\n", *videoSource->Imaging->ColorSaturation);
        }
        if (videoSource->Imaging->Contrast)
        {
                printf("      Contrast: %f\n", *videoSource->Imaging->Contrast);
        }
        if (videoSource->Imaging->Exposure)
        {

        }
        if (videoSource->Imaging->Focus)
        {

        }
        if (videoSource->Imaging->IrCutFilter)
        {

        }
        if (videoSource->Imaging->Sharpness)
        {
                printf("      Sharpness: %f\n", *videoSource->Imaging->Sharpness);
        }
        if (videoSource->Imaging->WideDynamicRange)
        {

        }
        if (videoSource->Imaging->WhiteBalance)
        {

        }
        if (videoSource->Imaging->Extension)
        {
          printf("      extension:\n");
          for (auto strPtr : videoSource->Imaging->Extension->__any)
          {
            printf("        %s\n", strPtr);
          }
        }
        if (videoSource->Imaging->__anyAttribute)
        {
                printf("      attr: %s\n", videoSource->Imaging->__anyAttribute);
        }
      }
      if (videoSource->__anyAttribute)
      {
        printf("    attr: %s\n", videoSource->__anyAttribute);
      }


    _trt__GetVideoSourceModes getVideoSourceModes;
    getVideoSourceModes.VideoSourceToken = videoSource->token;
    _trt__GetVideoSourceModesResponse getVideoSourceModesResponse;
    ret = proxy.GetVideoSourceModes(&getVideoSourceModes, getVideoSourceModesResponse);
    if (ret == 0)
    {
      printf("  Video Source modes:\n");
      for( auto sourceMode : getVideoSourceModesResponse.VideoSourceModes )
      {
        printf("    MaxFramerate: %f\n", sourceMode->MaxFramerate);
        printVideoResolution("    MaxResolution:", sourceMode->MaxResolution );
        printf("    Encodings: %s\n", sourceMode->Encodings.c_str());
        printf("    Reboot: %d\n", (int)sourceMode->Reboot);
        if (sourceMode->Description)
        {
                printf("    Description: %s\n", sourceMode->Description->c_str());
        }
        printf("    Token: %s\n", sourceMode->token.c_str());
        if (sourceMode->Enabled)
        {
                printf("    Enabled: %d\n", (int)sourceMode->Enabled);
        }
        if (sourceMode->__anyAttribute)
        {
                printf("    attr: %s\n", sourceMode->__anyAttribute);
        }
      }
    }



    }
  }

  _trt__GetProfiles getProfiles;
  _trt__GetProfilesResponse getProfilesResponse;
  ret = proxy.GetProfiles(&getProfiles, getProfilesResponse);
  if (ret == 0) {
    for (auto& profile : getProfilesResponse.Profiles)
    {
      printf("PROFILE Name: %s\n", profile->Name.c_str());

      printf("Token: %s\n", profile->token.c_str());
      if (profile->fixed) 
      {
        printf("Fixed: %d\n", (int)*profile->fixed);
      }
      if (profile->VideoSourceConfiguration)
      {
        printf("VIDEO SOURCE:\n");
        printf("  Name: %s\n", profile->VideoSourceConfiguration->Name.c_str());
        printf("  UseCount: %d\n", profile->VideoSourceConfiguration->UseCount);
        printf("  Token: %s\n", profile->VideoSourceConfiguration->token.c_str());
        printf("  Video source token: %s\n", profile->VideoSourceConfiguration->SourceToken.c_str());
        if (profile->VideoSourceConfiguration->Bounds) {
          tt__IntRectangle bounds = *profile->VideoSourceConfiguration->Bounds;
          printf("Video source bounds: %d %d %d %d\n", bounds.x, bounds.y, bounds.width, bounds.height);
        }
        if (profile->VideoSourceConfiguration->ViewMode) {
          printf("Video source viewmode: %s\n", profile->VideoSourceConfiguration->ViewMode->c_str());
        }
      }
      else printf("No video source conf\n");
      if (profile->AudioSourceConfiguration)
      {
        printf("  Name: %s\n", profile->AudioSourceConfiguration->Name.c_str());
        printf("  UseCount: %d\n", profile->AudioSourceConfiguration->UseCount);
        printf("  Token: %s\n", profile->AudioSourceConfiguration->token.c_str());
        printf("Audio source configuration: %s\n", profile->AudioSourceConfiguration->SourceToken.c_str());
      }
      else printf("No audio source conf\n");
      if (profile->VideoEncoderConfiguration)
      {
        printf("VIDEO ENCODER:\n");

        printf("  Name: %s\n", profile->VideoEncoderConfiguration->Name.c_str());
        printf("  UseCount: %d\n", profile->VideoEncoderConfiguration->UseCount);
        printf("  Token: %s\n", profile->VideoEncoderConfiguration->token.c_str());


        switch (profile->VideoEncoderConfiguration->Encoding) 
        {
          case tt__VideoEncoding::JPEG:
            printf("  Encoding: JPEG\n");
            break;
          case tt__VideoEncoding::MPEG4:
            printf("  Encoding: MPEG4\n");
            break;
          case tt__VideoEncoding::H264:
            printf("  Encoding: H264\n");
            break;
          default:
            printf("  Encoding: Unknown\n");
            break;
        }

        printVideoResolution("  Resolution: ", profile->VideoEncoderConfiguration->Resolution );

        printf("  Video encoder quality: %f\n", profile->VideoEncoderConfiguration->Quality);
        if (profile->VideoEncoderConfiguration->RateControl)
        {
          printf("    Rate control FrameRateLimit: %d\n", profile->VideoEncoderConfiguration->RateControl->FrameRateLimit);
          printf("    Rate control EncodingInterval: %d\n", profile->VideoEncoderConfiguration->RateControl->EncodingInterval);
          printf("    Rate control BitrateLimit: %d\n", profile->VideoEncoderConfiguration->RateControl->BitrateLimit);
        }
        if (profile->VideoEncoderConfiguration->MPEG4)
        {
          printf("    MPEG4 GovLength %d\n", profile->VideoEncoderConfiguration->MPEG4->GovLength);
          printf("    MPEG4 Profile %d\n", (int)profile->VideoEncoderConfiguration->MPEG4->Mpeg4Profile);
        }
        if (profile->VideoEncoderConfiguration->H264)
        {
          printf("    H264 GovLength %d\n", profile->VideoEncoderConfiguration->H264->GovLength);
          printf("    H264 Profile %d\n", (int)profile->VideoEncoderConfiguration->H264->H264Profile);
        }
        if (profile->VideoEncoderConfiguration->Multicast)
        {
          printMulticast("    ", profile->VideoEncoderConfiguration->Multicast );
        }
      }
      else printf("No video encoder conf\n");
      if (profile->AudioEncoderConfiguration)
      {
        printf("  AUDIO ENCODER:\n");
        printf("    Name: %s\n", profile->AudioEncoderConfiguration->Name.c_str());
        printf("    UseCount: %d\n", profile->AudioEncoderConfiguration->UseCount);
        printf("    Token: %s\n", profile->AudioEncoderConfiguration->token.c_str());
        printf("    type: %d\n", (int)profile->AudioEncoderConfiguration->Encoding);
        printf("    bitrate: %d\n", profile->AudioEncoderConfiguration->Bitrate);
        printf("    samplerate: %d\n", profile->AudioEncoderConfiguration->SampleRate);
        if (profile->AudioEncoderConfiguration->Multicast)
        {
          printMulticast("    ", profile->AudioEncoderConfiguration->Multicast);
        }
      }
      else printf("No audio encoder conf\n");
      if (profile->VideoAnalyticsConfiguration)
      {
        printf("VIDEO ANALYTICS:\n");
        printf("  Name: %s\n", profile->VideoAnalyticsConfiguration->Name.c_str());
        printf("  UseCount: %d\n", profile->VideoAnalyticsConfiguration->UseCount);
        printf("  Token: %s\n", profile->VideoAnalyticsConfiguration->token.c_str());
        printf("VIDEO ANALYTICS ENGINE:\n");
        for ( auto& config : profile->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->AnalyticsModule )
        {
          printConfig("  ", config );
        }
  //profile->VideoAnalyticsConfiguration->AnalyticsEngineConfiguration->Extension
        printf("VIDEO ANALYTICS RULES:\n");
        for ( auto& config : profile->VideoAnalyticsConfiguration->RuleEngineConfiguration->Rule )
        {
          printConfig("  ", config );
        }
  //profile->VideoAnalyticsConfiguration->RuleEngineConfiguration

      }
      else printf("No video analytics conf\n");

      _trt__GetStreamUri getStreamUri;
      getStreamUri.StreamSetup = new tt__StreamSetup();
      getStreamUri.ProfileToken = profile->token;
      _trt__GetStreamUriResponse getStreamUriResponse;
      ret = proxy.GetStreamUri( &getStreamUri, getStreamUriResponse );
      if (ret == 0) 
      {
        printf("  Stream:\n");    
        printMediaUri( getStreamUriResponse.MediaUri );
      }
      else
      {
        printf("  No stream URI\n");
      }


      _trt__GetSnapshotUri getSnapshotUri;
      getSnapshotUri.ProfileToken = profile->token;
      _trt__GetSnapshotUriResponse getSnapshotUriResponse;
      ret = proxy.GetSnapshotUri(&getSnapshotUri, getSnapshotUriResponse);
      if (ret == 0)
      {
        printf("  Snapshot:\n");
        printMediaUri( getSnapshotUriResponse.MediaUri );
      }
      else
      {
        printf("  No snapshot URI\n");
      }
      _trt__GetCompatibleMetadataConfigurations getMeta;
      getMeta.ProfileToken = profile->token;
      _trt__GetCompatibleMetadataConfigurationsResponse getMetaResponse;
      ret = proxy.GetCompatibleMetadataConfigurations( &getMeta, getMetaResponse );
      if (ret == 0)
      {
        printf("  Compatible metadata configurations:\n");
        for (auto conf : getMetaResponse.Configurations)
        {
          printf("    token: %s\n", conf->token.c_str());

          _trt__GetMetadataConfigurationOptions getMetadataConfOptions;
          getMetadataConfOptions.ConfigurationToken = &conf->token;
          getMetadataConfOptions.ProfileToken = &profile->token;
          _trt__GetMetadataConfigurationOptionsResponse getMetadataConfOptionsResponse;
          ret = proxy.GetMetadataConfigurationOptions( &getMetadataConfOptions, getMetadataConfOptionsResponse );
          if (ret == 0)
          {
            printf("    Metadata configuration options:\n");
            printMetadataConfigurationOptions( "      ",  getMetadataConfOptionsResponse.Options );
          }
          else
          {
            printf("    No Metadata configuration options\n");
          }


        }
      }


      _trt__GetMetadataConfigurationOptions getMetadataConfOptions;
      getMetadataConfOptions.ProfileToken = &profile->token;
      _trt__GetMetadataConfigurationOptionsResponse getMetadataConfOptionsResponse;
      ret = proxy.GetMetadataConfigurationOptions( &getMetadataConfOptions, getMetadataConfOptionsResponse );
      if (ret == 0)
      {
        printf("  Metadata configuration options:\n");
        printMetadataConfigurationOptions( "    ",  getMetadataConfOptionsResponse.Options );
      }
      else
      {
        printf("  No metadata configuration options\n");
      }

      printf("\n");


    }
  }


  _trt__GetMetadataConfigurations getMetadataConfigurations;
  _trt__GetMetadataConfigurationsResponse getMetadataConfigurationsResponse;
  ret = proxy.GetMetadataConfigurations( &getMetadataConfigurations, getMetadataConfigurationsResponse );
  if (ret == 0)
  {
    printf("Metadata configurations: \n");
    for (auto conf : getMetadataConfigurationsResponse.Configurations)
    {
      printMetadataConfiguration("  ", conf );
    }
  }
  _trt__GetMetadataConfigurationOptions getMetadataConfOptions;
  _trt__GetMetadataConfigurationOptionsResponse getMetadataConfOptionsResponse;
  ret = proxy.GetMetadataConfigurationOptions( &getMetadataConfOptions, getMetadataConfOptionsResponse );
  if (ret == 0)
  {
    printf("Metadata configuration options:\n");
    printMetadataConfigurationOptions( "  ",  getMetadataConfOptionsResponse.Options );
  }
  else
  {
    printf("No metadata configuration options\n");
  }

  _trt__GetOSDs getOSDs;
  _trt__GetOSDsResponse getOSDsResponse;
  ret = proxy.GetOSDs(&getOSDs, getOSDsResponse);
  if (ret == 0)
  {
    printf("OSDs:\n");
    for( auto& osd : getOSDsResponse.OSDs )
    {
      printf("  token: %s\n", osd->token.c_str());
      printf("  type: %d\n", (int)osd->Type);
      if (osd->Position)
      {
        printf("  Position:\n");
        printf("    Type: %s\n", osd->Position->Type.c_str());
        if (osd->Position->Pos)
        {
          printf("    %f : %f\n", *osd->Position->Pos->x, *osd->Position->Pos->y);
        }
        if (osd->Position->Extension)
        {
          printf("    Extension:\n");
          for (auto strPtr : osd->Position->Extension->__any)
          {
            printf("      %s\n", strPtr);
          }
        }
        if (osd->Position->__anyAttribute)
        {
          printf("      attr: %s\n", osd->Position->__anyAttribute);
        }
      }
      if (osd->TextString)
      {
        printf("  TextString:\n");
        printf("    Type: %s\n", osd->TextString->Type.c_str());
        if (osd->TextString->DateFormat)
        {
          printf("    DateFormat: %s\n", osd->TextString->DateFormat->c_str());
        }
        if (osd->TextString->TimeFormat)
        {
          printf("    TimeFormat: %s\n", osd->TextString->TimeFormat->c_str());
        }
        if (osd->TextString->FontSize)
        {
          printf("    FontSize: %d\n", *osd->TextString->FontSize);
        }
        if (osd->TextString->FontColor)
        {
          printf("    FontColor:\n");
        }
        if (osd->TextString->BackgroundColor)
        {
          printf("    BackgroundColor:\n");
        }
        if (osd->TextString->PlainText)
        {
          printf("    PlainText: %s\n", osd->TextString->PlainText->c_str());
        }
      }
      if (osd->Image)
      {
        printf("  Image:\n");
      }
      if (osd->Extension)
      {
        printf("  extension:\n");
        for (auto strPtr : osd->Extension->__any)
        {
          printf("    %s\n", strPtr);
        }
      }
      if (osd->__anyAttribute)
      {
        printf("  attr: %s\n", osd->__anyAttribute);
      }
    }
  }

  return 0;
}
