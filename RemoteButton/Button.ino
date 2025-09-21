#include "Button.h"

void Button::gather()
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