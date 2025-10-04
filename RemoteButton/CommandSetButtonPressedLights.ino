#include "CommandSetButtonPressedLights.h"

void CommandSetButtonPressedLights::set_default()
{
  commands.emplace_back( 200,   0,   0, 100 );
  commands.emplace_back( 200, 200,   0, 100 );
  commands.emplace_back( 200,   0, 200, 100 );
  commands.emplace_back(   0,   0, 200, 100 );
}

void CommandSetButtonReleasedLights::set_default()
{
  commands.emplace_back( 200,   0,   0, 100 );
  commands.emplace_back( 200, 200,   0, 100 );
  commands.emplace_back( 200,   0, 200, 100 );
  commands.emplace_back(   0, 100,   0, 100 );
}
