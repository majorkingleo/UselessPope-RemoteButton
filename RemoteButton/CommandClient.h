#ifndef COMMAND_CLIENT_H
#define COMMAND_CLIENT_H

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <LedCommandSequence.h>
#include <optional>

class CommandClient
{
private:
  WiFiClient client;
  WiFiServer & server;
  std::vector<LedCommandSequence*> commands;
  String       data;
  
public:
  CommandClient( WiFiServer & server_ )
  : server(server_)
  {}

  void add( LedCommandSequence *command ) {
    commands.push_back( command );
  }

  std::optional<IPAddress> operator()();
};

#endif