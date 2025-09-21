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
#include <Adafruit_NeoPixel.h>

const unsigned PIN_BUTTON_BOOT_0 = 0;
const unsigned PIN_BUTTON = 19;
const unsigned PIN_LED1 = 32;

class Button
{
  enum STATE {
    STATE_NOT_PRESSED = 0,
    STATE_PRESSED 
  };

  STATE state = STATE_NOT_PRESSED;
  bool state_changed = false;
  int  pin;
public:

  Button( int pin_ )
  : pin( pin_ )
  {}

  int get_pin() const { return pin; }

  virtual void gather()
  {
    STATE pin_data;
    
    if( digitalRead(pin) > 0 ) {
      pin_data = STATE_PRESSED;
    } else {
      pin_data = STATE_NOT_PRESSED;
    }

    if( state != pin_data ) {
      state_changed = true;
      state = pin_data;
    }
  }

  bool did_button_changed_state() const {
    return state_changed;
  }

  bool was_button_pressed() const {
    if( state == STATE_PRESSED ) {
      return true;
    }

    return false;
  }

  void reset() {
    state_changed = false;
  }
};

class CountButton : public Button
{
  int count_start;
  int count_end;
  int count;

  public:
  CountButton( int pin_, int count_start_ = 0, int count_end_ = 1 )
  : Button( pin_ ),
  count_start( count_start_ ),
  count_end( count_end_ ),
  count( count_start_ )
  {}

  void gather() override
  {
    Button::gather();

    if( did_button_changed_state() ) {
      if( was_button_pressed() ) {
        count = count+1;

        if( count > count_end ) {
          count = count_start;
        }
      } else {
        reset();
      }
    }
  }

  int get_count() const {
    return count;
  }
};

void initWiFi() 
{
  WiFi.mode(WIFI_STA);
  WiFi.begin("TKZiegelstrasseSlow", "internet");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("wifi: "); Serial.println(WiFi.localIP().toString());
  Serial.print("mac:  "); Serial.println(WiFi.macAddress());
}

//CountButton button_boot( PIN_BUTTON_BOOT_0 );
CountButton button_boot( PIN_BUTTON );

Adafruit_NeoPixel led1(1,PIN_LED1);

void setup() {
  Serial.begin(115200);
  pinMode(button_boot.get_pin(),INPUT);
  pinMode(PIN_LED1,OUTPUT);
  led1.begin();
  led1.setPixelColor(0,150,0,0);
  led1.show();

  initWiFi();
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
        led1.setPixelColor(0,255,255,255);
        led1.show();

      } else {
        Serial.write( "PIN_WEICHE_2, LOW\n" );
        led1.setPixelColor(0,255,255,255);
        led1.show();
      }
  }

  delay(50);

}
