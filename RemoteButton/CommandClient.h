#ifndef COMMAND_CLIENT_H
#define COMMAND_CLIENT_H

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <LedCommandSequence.h>

class CommandClient
{
private:
  WiFiClient client;
  WiFiServer & server;
  LedCommandSequence & commands;
  String       data;
  
public:
  CommandClient( WiFiServer & server_, LedCommandSequence & commands_ )
  : server(server_), commands(commands_)
  {}

  void operator()();
};

#endif