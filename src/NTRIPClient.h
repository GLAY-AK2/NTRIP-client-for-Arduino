#ifndef NTRIP_CLIENT
#define NTRIP_CLIENT

#include <WiFi.h>
#include <Arduino.h>

class NTRIPClient : public WiFiClient{
  private :
  char *_host;
  int  _port;
  char *_mntpnt;
  char *_user;
  char *_psw;
  byte _buffer[512];
  const char* encbase64(const unsigned char *byte, int n);
  
  public :
  using WiFiClient::connect;
  NTRIPClient(char* host,int port,char* mntpnt,char* user,char* psw);
  bool reqSrcTbl();   //request MountPoints List serviced the NTRIP Caster 
  bool reqRaw();      //request RAW data from Caster  
  char *readLine();
  int connect();
  
};

#endif
