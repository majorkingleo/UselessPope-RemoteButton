#include "LedCommandSequence.h"

bool LedCommandSequence::parse( String command )
  {    
    int pos = command.indexOf( COMMAND.c_str() ); 

    if( pos < 0 ) {
      return false;
    }

    command = command.substring( pos + COMMAND.length() );

    command = command.substring(0,-1);

    for( unsigned idx = 0; idx + 8 < command.length(); idx += 8 ) {
      commands.clear();
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