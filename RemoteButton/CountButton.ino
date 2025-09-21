#include "CountButton.h"

void CountButton::gather()
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