#include "Class_Star.h"
#include "Class_Timer.h"

Class_Star::Class_Star(Pos_RC map_pos, UnitType type)
  :Class_Unit(map_pos, type) {
  duration = Class_Timer::GetGameTime() + StarDuration;
}

DWORD Class_Star::GetDuration()const {
  return duration;
}
