#pragma once
#include "Class_Unit.h"

const int StarDuration = 600;//星星的持续时间（毫秒）

class Class_Star :
  public Class_Unit {
public:
  Class_Star(Pos_RC map_pos, UnitType type);//构造函数，需要知道该星星的地图坐标和创建星星的单位类型

  //获取星星的持续时间
  DWORD GetDuration()const;

private:
  DWORD duration;//记录星星消失的时间点
};
