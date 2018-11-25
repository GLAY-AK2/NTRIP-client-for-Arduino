/*
 *  NTRIP client for Arduino Ver. 1.0.0 
 *  NTRIPClient Sample
 *  Request Source Table (Source Table is basestation list in NTRIP Caster)
 *  Request Reference Data 
 * 
 * 
 */
#include "NTRIPClient.h"

const char* ssid     = "your_ssid";
const char* password = "your_password";

char* host = "ntrip caster host";
int httpPort = 2101;
char* mntpnt = "ntrip caster's mountpoint";
char* user   = "ntrip caster's client user";
char* passwd = "ntrip caster's client password";
NTRIPClient ntrip_c(host,httpPort,mntpnt,user,passwd);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!ntrip_c.connect()) {
    Serial.println("connection failed\n");
    return;
  }
  
  Serial.println("Requesting SourceTable.");
  if(ntrip_c.reqSrcTbl()){
    delay(5);
    while(ntrip_c.available()){
      ntrip_c.readLine();  
    }
  }
  else{
    Serial.println("SourceTable request error");
  }
  Serial.print("Requesting SourceTable is OK\n");
  ntrip_c.stop();
  
  if (!ntrip_c.connect()) {
    Serial.println("connection failed\n");
    return;
  }
  Serial.println("Requesting MountPoint's Raw data");
  if(!ntrip_c.reqRaw()){
    delay(15000);
    ESP.restart();
  }
  Serial.println("Requesting MountPoint is OK");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ntrip_c.available()) {
        char ch = ntrip_c.read();        
        Serial.print(ch);
        
  }
}
