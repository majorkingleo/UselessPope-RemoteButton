#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <LedCommandSequence.h>
#include <CountButton.h>
#include <CommandClient.h>
#include <MultiWiFi.h>
#include <CommandSetButtonPressedLights.h>
#include <SendAction.h>
#include <optional>

const unsigned PIN_BUTTON_BOOT_0 = 0;
const unsigned PIN_BUTTON = 19;
const unsigned PIN_LED1 = 32;



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
Button button( PIN_BUTTON );
WiFiServer server(80); // Port 80
Adafruit_NeoPixel led1(1,PIN_LED1);
CommandSetButtonPressedLights command_set_button_pressed_lights(led1, 0 );
CommandSetButtonReleasedLights command_set_button_released_lights(led1, 0 );
CommandClient client( server );
std::optional<SendAction> send_action;
unsigned long last_ping_deadline = 0;

void initMultiWiFi() 
{
  MultiWiFi multi_wifi;

  WiFi.mode(WIFI_STA);
  multi_wifi.add("TKPapst", "johannespaul");

  Serial.print("Connecting to WiFi ..");
  while(multi_wifi.run() != WL_CONNECTED) {
    Serial.print('cannot connect to Wifi');
    led1.setPixelColor( 0, 100, 0, 0 );
    led1.show();
    delay(500);
  }
  Serial.print("wifi: "); Serial.println(WiFi.localIP().toString());
  Serial.print("mac:  "); Serial.println(WiFi.macAddress()); 

  send_action.emplace();

  led1.setPixelColor( 0, 0, 100, 0 );
  led1.show();
}

void setup() {
  Serial.begin(115200);
  pinMode(button.get_pin(),INPUT);
  pinMode(PIN_LED1,OUTPUT);
  led1.begin();
  led1.setPixelColor(0,100,100,0);
  led1.show();

  //initWiFi();
  initMultiWiFi();

  server.begin();
  server.setNoDelay(true);

  client.add( &command_set_button_pressed_lights );
  client.add( &command_set_button_released_lights );

  button.set_inverted( true );
}

void loop() {

  button.gather();

  if( button.did_button_changed_state() ) {

      button.reset();

      if( button.was_button_pressed() ) {
        send_action->send("ButtonPressed");
        Serial.write( "pressed\n" );

        command_set_button_pressed_lights.play();
        //led1.setPixelColor(0,100,000,60,60);
        //led1.show();

      } else {
        send_action->send("ButtonReleased");
        Serial.write( "released\n" );

        command_set_button_released_lights.play();
        //led1.setPixelColor(0,0,0,100,60);
        //led1.show();

      }

  }

  if( last_ping_deadline < millis() ) {
    last_ping_deadline = millis() + 10000;
    send_action->send("Ping");
  }

  command_set_button_pressed_lights();
  command_set_button_released_lights();
  std::optional<IPAddress> o_connection = client();
  
  if( o_connection ) {
    send_action->add_server_ip( *o_connection );
  }

  //delay(50);
}
