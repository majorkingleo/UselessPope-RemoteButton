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
private:
  std::vector<Command> commands;
  Adafruit_NeoPixel & led;

public:

  LedCommandSequence( Adafruit_NeoPixel & led_ )
  : led( led_ )
  {

  }

  bool parse( String command );

  bool parseOneCommand( const String & command );

  bool getColor( uint8_t & color, String code );

  bool getDelay( unsigned short & delay, String code );
};
#endif