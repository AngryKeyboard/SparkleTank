/****************************************************************************************
 * Copyright © 2019 - 2023 by AngryKeyboard.
 * %Project% is licensed under MulanOWL BY v1.
 * You can use this software according to the terms and conditions of the MulanOWL BY v1.
 * You may obtain a copy of MulanOWL BY v1 at:
 *          http://license.coscl.org.cn/MulanOWLBYv1
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the MulanOWL BY v1 for more details.
****************************************************************************************/
#pragma once
#include "Class_Unit.h"

//坦克基类只保留最基本的、所有坦克都有的数据
class Class_Tank :
  public Class_Unit {
private:
  Direction direction;//方向
  Armor Armor_Level;//保存当前装甲等级（装甲等级通过拾取道具提升，同时影响坦克的火力情况）

public:
  Class_Tank(Pos_XY pos_px, UnitType type, Direction dir = DOWN, Armor Lev = NORMAL);

  /**********
  Get系列函数
  **********/
  Direction GetDirection()const;
  Armor GetArmorLev()const;

  /**********
  Set系列函数
  **********/
  //改变方向
  void SetDirection(Direction);
  //设置装甲等级
  void SetArmorLev(Armor);
};

inline Direction Class_Tank::GetDirection()const {
  return direction;
}

inline Armor Class_Tank::GetArmorLev()const {
  return Armor_Level;
}

inline void Class_Tank::SetDirection(Direction newDirection) {
  direction = newDirection;
}

inline void Class_Tank::SetArmorLev(Armor newArmorLev) {
  Armor_Level = newArmorLev;
}
