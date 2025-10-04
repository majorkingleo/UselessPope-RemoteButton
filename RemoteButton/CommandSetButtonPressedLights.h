#ifndef COMMAND_SET_BUTTON_PRESSED_LIGHTS
#define COMMAND_SET_BUTTON_PRESSED_LIGHTS

#include "LedCommandSequence.h"

class CommandSetButtonPressedLights : public LedCommandSequence
{
public:
  CommandSetButtonPressedLights(  Adafruit_NeoPixel & led_, unsigned led_idx_ )
    : LedCommandSequence( led_, led_idx_, "SetButtonPressedLights=" )
  {
    set_default();
  }

  void set_default();
};

class CommandSetButtonReleasedLights : public LedCommandSequence
{
public:
  CommandSetButtonReleasedLights(  Adafruit_NeoPixel & led_, unsigned led_idx_ )
    : LedCommandSequence( led_, led_idx_, "SetButtonReleasedLights=" )
  {
    set_default();
  }

  void set_default();
};


#endif