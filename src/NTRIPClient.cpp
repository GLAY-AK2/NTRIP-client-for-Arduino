#include "NTRIPClient.h"

NTRIPClient::NTRIPClient(char* host,int port,char* mntpnt,char* user,char* psw)
{
  _host = host;
  _port = port;
  _mntpnt = mntpnt;
  _user = user;
  _psw = psw;
}

int NTRIPClient::connect()
{
  return connect(_host,_port);
}

const char* NTRIPClient::encbase64(const unsigned char *byte, int n)
{
    const char table[]=
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i,j,k,b;
    String str; 
    
    Serial.println("passwd encording");
    
    for (i=j=0;i/8<n;) {
        for (k=b=0;k<6;k++,i++) {
            b<<=1; if (i/8<n) b|=(byte[i/8]>>(7-i%8))&0x1;
        }
        str = str + table[b];
    }
    while (j&0x3) str = str + '=';
    
    Serial.println("passwd encorded!\n");
    return str.c_str();
}

bool NTRIPClient::reqSrcTbl()
{
  String p="";
  p = String("GET ") + String("/") + String(" HTTP/1.0\r\n");
  p = p + String("User-Agent: NTRIP Enbeded\r\n");
  print(p);
  unsigned long timeout = millis();
  while (available() == 0) {
     if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        stop();
        return false;
     }
  }
  readLine();
  if(strncmp((char*)_buffer,"SOURCETABLE 200 OK",17))
  {
    Serial.print((char*)_buffer);
    return false;
  }
  return true;
}

bool NTRIPClient::reqRaw()
{
  String p="";
    String auth="";
    Serial.println("Request Ntrip");
    
    p = String("GET ") + String("/") + _mntpnt + String(" HTTP/1.0\r\n");
    p = p + String("User-Agent: NTRIP Enbeded\r\n");
    
    if (strlen(_user)==0) {
        p = p + String("Accept: */*\r\n");
        p = p + String("Connection: close\r\n");
    }
    else {
        auth = _user + String(":") + _psw;
        Serial.println(auth);
        p = p + String("Authorization: Basic ");
        p = p + encbase64((unsigned char *)auth.c_str(),strlen(auth.c_str()));
        p = p + String("\r\n");
    }
    p = p + String("\r\n");
    print(p);
    Serial.println(p);
    unsigned long timeout = millis();
    while (available() == 0) {
        if (millis() - timeout > 50000) {
            Serial.println("Client Timeout !");
            return false;
        }
    }
    readLine();
    if(strncmp((char*)_buffer,"ICY 200 OK",10))
    {
      Serial.print((char*)_buffer);
      return false;
    }
    return true;
}

char* NTRIPClient::readLine()
{
  int len = 0;
  while(available()) {
    _buffer[len] = read();
    len++;
    if(_buffer[len-1] == '\n' || len > 510) break;
  }
  _buffer[len]='\0';
  Serial.print((char*)_buffer); 
  return (char*)_buffer;
}
