#ifndef SEND_ACTION_H
#define SEND_ACTION_H

#include <WiFiUdp.h>
#include <WiFiType.h>
#include <set>

class SendAction
{
private:
  WiFiUDP Udp;
  const String localIP{};
  const String macAddress{};

  std::set<IPAddress> server_ips{};
public:

  SendAction();

  void add_server_ip( const IPAddress & address );

  void send( const String & action );
};

#endif