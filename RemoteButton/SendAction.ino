#include "SendAction.h"
#include <WiFi.h>

SendAction::SendAction()
: localIP( WiFi.localIP() ),
  macAddress( WiFi.macAddress() )
{
  /*
  uint8_t bytes[4];
  const IPAddress netmask = WiFi.netmask();
  IPAddress broadcastIP{ WiFi.localIP() };

  for( unsigned i = 0; i < 4; ++i ) {
    if( netmask[i] != 255 ) {

    }
  }
  */
  add_server_ip( IPAddress{ 255, 255, 255, 255 } );
  add_server_ip( IPAddress{ 192, 168, 1, 19 } );
}


void SendAction::add_server_ip( const IPAddress & address )
{
  server_ips.insert( address );
}

void SendAction::send( const String & action )
{
  const String msg = macAddress + ";" + localIP + ";Action=" + action + "\n";

  for( const auto & ip : server_ips ) {
    Udp.beginPacket(ip,22000);    
    Udp.write(reinterpret_cast<const uint8_t*>(msg.c_str()),msg.length());
    Udp.endPacket();
  }
}