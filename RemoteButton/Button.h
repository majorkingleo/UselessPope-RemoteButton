#ifndef BUTTON_H
#define BUTTON_H

class Button
{
  enum STATE {
    STATE_NOT_PRESSED = 0,
    STATE_PRESSED 
  };

  STATE state = STATE_NOT_PRESSED;
  bool state_changed = false;
  int  pin;
  unsigned long last_check = 0;
  static constexpr const unsigned long rebounce_time = 30;

public:

  Button( int pin_ )
  : pin( pin_ )
  {}

  int get_pin() const { return pin; }

  virtual void gather();

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
#endif