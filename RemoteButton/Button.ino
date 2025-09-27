#include "Button.h"

void Button::gather()
{
  STATE pin_data;

  if( last_check + rebounce_time > millis() ) {
    return;
  }
  
  if( digitalRead(pin) > 0 ) {
    pin_data = STATE_PRESSED;
  } else {
    pin_data = STATE_NOT_PRESSED;
  }

  if( state != pin_data ) {
    state_changed = true;
    state = pin_data;
  }

  last_check = millis();
}