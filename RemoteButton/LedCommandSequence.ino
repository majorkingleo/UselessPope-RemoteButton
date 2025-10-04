#include "LedCommandSequence.h"


String LedCommandSequence::Command::to_string() const
{
  char acBuffer[50];
  snprintf( acBuffer, sizeof(acBuffer), "%02X%02X%02X%04X", red, green, blue, delay);
  return acBuffer;
}

bool LedCommandSequence::parse( String command )
  {    
    int pos = command.indexOf( COMMAND.c_str() ); 

    if( pos < 0 ) {
      return false;
    }

    command = command.substring( pos + COMMAND.length() );
    command = command.substring(0,-1);
    commands.clear();

    for( unsigned idx = 0; idx + 8 < command.length(); idx += 8 ) {      
      parseOneCommand( command.substring(idx,idx+8) );
    }

    return true;
  }

  bool LedCommandSequence::parseOneCommand( const String & command )
  {
    // Serial.write( ">" );
    // Serial.write( command.c_str() );
    // Serial.write( "<\n" );

    // RRGGBBDD
    if( command.length() < 8 ) {      
      Serial.write("invalid command length");
      return false;
    }

    Command cmd;
    if( !getColor( cmd.red,   command.substring(0,2) ) ) {
      return false;
    }
  
    if( !getColor( cmd.green, command.substring(2,4) ) ) {
      return false;
    }

    if( !getColor( cmd.blue,  command.substring(4,6) ) ) {
      return false;
    }

    if( !getDelay( cmd.delay, command.substring(6,10) ) ) {
      return false;
    }

    Serial.write( "command: " );
    Serial.write( cmd.to_string().c_str() );
    Serial.write( "\n" );

    commands.push_back( cmd );

    return true;
  }

  bool LedCommandSequence::getColor( uint8_t & color, String code ) {
    color = {};
    if( sscanf( code.c_str(), "%hhX", &color ) != 1 ) {
      return false;
    }

    /*
      Serial.write("color parsed from >");
      Serial.write(code.c_str());
      Serial.write("< to ");
      Serial.write((int)color);
      Serial.write("\n");
    */
    
    return true;
  }

  bool LedCommandSequence::getDelay( unsigned short & delay, String code ) {
    delay = {};
    if( sscanf( code.c_str(), "%hX", &delay ) != 1 ) {
      return false;
    }

    return true;
  }

  void LedCommandSequence::play()
  {
    playing     = true;
    playing_idx = 0;
    playing_millis_next = 0;
  }

  void LedCommandSequence::operator()()
  {
    if( !playing ) {
      return;
    }

    if( playing_millis_next < millis() ) {
      if( playing_idx >= commands.size() ) {
        playing_idx = 0;
        playing = false;
        return;
      }

      Command & cmd = commands.at(playing_idx);
      Serial.write(String("playing: "  + cmd.to_string() + "\n").c_str());

      led.setPixelColor( LED_IDX, cmd.red, cmd.green, cmd.blue );
      led.show();
      playing_millis_next = millis() + cmd.delay;
      playing_idx++;
    }
  }