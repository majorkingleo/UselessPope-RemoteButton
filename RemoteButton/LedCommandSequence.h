#ifndef LEDCOMMANDSEQUENCE_H
#define LEDCOMMANDSEQUENCE_H
#include <Adafruit_NeoPixel.h>

class LedCommandSequence
{
public:
  struct Command
  {
    uint8_t         red;
    uint8_t         green;
    uint8_t         blue;
    unsigned short  delay;
  };
protected:
  std::vector<Command> commands;
  Adafruit_NeoPixel & led;
  const String COMMAND;
  const unsigned LED_IDX;

  bool          playing = false;
  unsigned      playing_idx = 0;
  unsigned long playing_millis_next = 0;


public:

  LedCommandSequence( Adafruit_NeoPixel & led_, unsigned led_idx_, const String & command_ )
  : led( led_ ),
    COMMAND( command_ ),
    LED_IDX( led_idx_ )
  {

  }

  bool parse( String command );

  bool parseOneCommand( const String & command );

  bool getColor( uint8_t & color, String code );

  bool getDelay( unsigned short & delay, String code );

  void play();

  void operator()();
};
#endif