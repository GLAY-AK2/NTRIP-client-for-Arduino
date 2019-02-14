#ifndef NTRIP_CLIENT
#define NTRIP_CLIENT

#include <WiFiClient.h>
#include <Arduino.h>
#include<base64.h>

class NTRIPClient : public WiFiClient{
  public :
  bool reqSrcTbl(char* host,int &port);   //request MountPoints List serviced the NTRIP Caster 
  bool reqRaw(char* host,int &port,char* mntpnt,char* user,char* psw);      //request RAW data from Caster 
  bool reqRaw(char* host,int &port,char* mntpnt); //non user
  int readLine(char* buffer,int size);

  
};

#endif
