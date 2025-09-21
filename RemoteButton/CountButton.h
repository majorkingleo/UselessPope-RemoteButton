#include "Button.h"
#ifndef COUNTBUTTON_H
#define COUNTBUTTON_H

class CountButton : public Button
{
  int count_start;
  int count_end;
  int count;

  public:
  CountButton( int pin_, int count_start_ = 0, int count_end_ = 1 )
  : Button( pin_ ),
  count_start( count_start_ ),
  count_end( count_end_ ),
  count( count_start_ )
  {}

  void gather() override;

  int get_count() const {
    return count;
  }
};
#endif