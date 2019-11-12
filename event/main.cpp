#include "PullPointSubscriptionBinding.nsmap"
#include "soapPullPointSubscriptionBindingProxy.h"
#include <stdio.h>



int main( int argc, char* argv[] )
{
  int ret;
  if (argc < 2) {
    printf("Usage:\n  %s http://server:8899\n", argv[0]);
    exit(1);
  }
  PullPointSubscriptionBindingProxy proxy(argv[1]);
#if 0
  _wsnt__GetMessages getMessages;
  std::string maxnum = "10";
  getMessages.MaximumNumber = &maxnum;
  _wsnt__GetMessagesResponse getMessagesResponse;
  ret = proxy.GetMessages( &getMessages, getMessagesResponse );
  if( ret == 0)
  {
    for( auto& msg : getMessagesResponse.NotificationMessage )
    {
      printf("%s\n", msg->Message.__any);
    }
  }
  {
    _wsnt__Subscribe subscribe;
    subscribe.ConsumerReference.Address = "http://172.16.0.19:8081/onvif";
    _wsnt__SubscribeResponse response;
    ret = proxy.Subscribe( &subscribe, response );
    if (ret == 0)
    {
      printf("%s %d\n", response.SubscriptionReference.Address, response.SubscriptionReference.__size);
      if (response.CurrentTime)
      {
        printf("CurrentTime: %llu\n", (unsigned long long)*response.CurrentTime);
      }
      if (response.TerminationTime)
      {
        printf("TerminationTime: %llu\n", (unsigned long long)*response.TerminationTime);
      }
      printf("Now: %llu\n", (unsigned long long)time(NULL));
    }
  }
#endif
  {
    _tev__CreatePullPointSubscription subscribePullPoint;
    std::string timeout = "PT30M";
    subscribePullPoint.InitialTerminationTime = &timeout;
    _tev__CreatePullPointSubscriptionResponse response;
    ret = proxy.CreatePullPointSubscription( &subscribePullPoint, response );
    if (ret == 0)
    {
      printf("Subscription reference: %s\n", response.SubscriptionReference.Address);
      for (int i=0; i<response.SubscriptionReference.__size; ++i)
      {
        printf("  %s\n", response.SubscriptionReference.__any[i]);
      }
      printf("CurrentTime: %llu\n", (unsigned long long)response.wsnt__CurrentTime);
      printf("TerminationTime: %llu\n", (unsigned long long)response.wsnt__TerminationTime);
      printf("Now: %llu\n", (unsigned long long)time(NULL));
      for( auto strPtr : response.__any )
      {
        printf("  %s\n", strPtr);
      }

      {
        PullPointSubscriptionBindingProxy proxy(response.SubscriptionReference.Address);

        while( response.wsnt__TerminationTime -1 > time(NULL) )
        {
          _tev__PullMessages pullMessages;
          pullMessages.MessageLimit = 10;
          pullMessages.Timeout = 360000;
          _tev__PullMessagesResponse response;
          ret = proxy.PullMessages( &pullMessages, response );
          if( ret == 0)
          {
            printf("Message:\n");
            for( auto& msg : response.wsnt__NotificationMessage )
            {
              if (msg->SubscriptionReference)
              {
                printf("  Subscription Reference: %s\n", msg->SubscriptionReference->Address);
              }
              if (msg->Topic)
              {

              }
              if (msg->ProducerReference)
              {
                printf("  Subscription Reference: %s\n", msg->ProducerReference->Address);
              }
              printf(" %s\n", msg->Message.__any);
            }
            printf("\n");
          }
          else
          {
            printf("  PullMessages failed\n");
          }
        }
      }
    }
    else
    {
      printf("CreatePullPointSubscription failed\n");
    }
  }
  return 0;
}
