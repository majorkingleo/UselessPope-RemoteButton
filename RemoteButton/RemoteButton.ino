#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <LedCommandSequence.h>
#include <CountButton.h>
#include <CommandClient.h>
#include <MultiWiFi.h>

const unsigned PIN_BUTTON_BOOT_0 = 0;
const unsigned PIN_BUTTON = 19;
const unsigned PIN_LED1 = 32;



void initMultiWiFi() 
{
  MultiWiFi multi_wifi;

  WiFi.mode(WIFI_STA);
  multi_wifi.add("TKZiegelstrasseSlow", "internet");
  multi_wifi.add("TKZiegelstrasseFast", "internet");

  Serial.print("Connecting to WiFi ..");
  while(multi_wifi.run() != WL_CONNECTED) {
    Serial.print('cannot connect to Wifi');
  }
  Serial.print("wifi: "); Serial.println(WiFi.localIP().toString());
  Serial.print("mac:  "); Serial.println(WiFi.macAddress()); 
}

void initWiFi() 
{
  WiFi.mode(WIFI_STA);
  WiFi.begin("TKZiegelstrasseFast", "internet");

  Serial.print("Connecting to WiFi ..");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("wifi: "); Serial.println(WiFi.localIP().toString());
  Serial.print("mac:  "); Serial.println(WiFi.macAddress()); 
}

//CountButton button_boot( PIN_BUTTON_BOOT_0 );
CountButton button_boot( PIN_BUTTON );
WiFiServer server(80); // Port 80
Adafruit_NeoPixel led1(1,PIN_LED1);
LedCommandSequence commands(led1, "SetButtonPressed=" );
CommandClient client( server, commands );

void setup() {
  Serial.begin(115200);
  pinMode(button_boot.get_pin(),INPUT);
  pinMode(PIN_LED1,OUTPUT);
  led1.begin();
  led1.setPixelColor(0,150,0,0);
  led1.show();

  //initWiFi();
  initMultiWiFi();

  server.begin();
  server.setNoDelay(true);
}

void loop() {

  button_boot.gather();

  if( button_boot.did_button_changed_state() ) {
      char acBuffer[10];
      sprintf( acBuffer, "Weiche %d\n", button_boot.get_count() );
      Serial.write( acBuffer );
      button_boot.reset();

      if( button_boot.get_count() == 0 ) {
        Serial.write( "PIN_WEICHE_1, LOW\n" );
        led1.setPixelColor(0,100,000,60,60);
        led1.show();

      } else {
        Serial.write( "PIN_WEICHE_2, LOW\n" );
        led1.setPixelColor(0,0,0,100,60);
        led1.show();
      }
  }

  client();

  //delay(50);
}
