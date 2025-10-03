#include "SendAction.h"
#include <WiFi.h>
#include <list>

namespace {

  class Message
  {
    std::list<std::pair<String, String>> data;
  public:

    Message( unsigned long count )
    {
      add( "TIME", millis() );
      add( "SEQ", count );
    }

    void add(  const String & key, const auto & value )
    {
        data.emplace_back( key, value );
    }

    String to_string() const 
    {
        String ret;

        for( auto & p : data ) {
          if( !ret.isEmpty() ) {
            ret += ";";
          }

          ret += p.first + "=" + p.second;
        }

        return ret;
    }
  };
}

SendAction::SendAction()
: localIP( WiFi.localIP().toString() ),
  macAddress( WiFi.macAddress() )
{
  uint32_t local_ip = WiFi.localIP();
  uint32_t broadcast_ip = local_ip | ( ~ (uint32_t)WiFi.subnetMask() );

  Serial.write("Broadcastip=");
  Serial.write( IPAddress{ broadcast_ip }.toString().c_str() );
  Serial.write("\n");


  add_server_ip( IPAddress{ broadcast_ip } );
  //add_server_ip( IPAddress{ 255, 255, 255, 255 } );
  //add_server_ip( IPAddress{ 192, 168, 1, 19 } );
}


void SendAction::add_server_ip( const IPAddress & address )
{
  server_ips.insert( address );
}

void SendAction::send( const String & action )
{
  Message msg( count++ );

  msg.add( "MAC", macAddress );
  msg.add( "IP", localIP );
  msg.add( "ACTION", action );

  const String msg_data = msg.to_string() + "\n";

  for( const auto & ip : server_ips ) {
    Udp.beginPacket(ip,22000);    
    Udp.write(reinterpret_cast<const uint8_t*>(msg_data.c_str()),msg_data.length());
    Udp.endPacket();
  }
}