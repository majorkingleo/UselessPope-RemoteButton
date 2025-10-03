#include "CommandClient.h"

std::optional<IPAddress> CommandClient::operator()()
{
  std::optional<IPAddress> ret;

  if( !client ) {
    client = server.accept();
    if( !client ) {
      return {};
    }

    data.clear();    
    Serial.write( "new connection\n" );
    ret = client.remoteIP();
  }

  if( !client.connected() ) {
    client.stop();
    data.clear();
    Serial.write( "connection endet\n" );
    return {};
  }

  if( client.available() ) {
    String new_data = client.readString();

    if( ( new_data.indexOf("\n\n") != -1 ) ||
        ( new_data.indexOf("\r\n\r\n") != -1 ) ) 
    {
      Serial.write( "Sending response\n" );
      client.println("HTTP/1.0 200 OK");
      client.println("Content-type:text/html");
      client.println("done\n");
      client.println();
      client.println();
    }    

    data += new_data;      
  }

  while( !data.length() == 0 )
  {
    int pos = data.indexOf( "\n" );
    String line = data.substring(0,pos);
    data = data.substring(pos+1);

    if( line.length() == 0 ) {
      continue;
    }

    /*
    Serial.write(line.c_str());

    if( !line.endsWith( "\n" ) ) {
      Serial.write("\n");
    }
    */

    for( auto command : commands ) {
      if( command->parse(line) ) {
        client.println("OK\n");
        client.stop();
        break;
      }
    }
  }

  return ret;
}