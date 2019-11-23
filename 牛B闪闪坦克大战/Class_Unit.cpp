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
#include "Class_Unit.h"


Class_Unit::Class_Unit(Pos_RC map_pos, UnitType type, Direction dir)
  :map_pos(map_pos), type(type), direction(dir), Armor_Level(NORMAL) {
  unit_pos.row = map_pos.row * 2;
  unit_pos.col = map_pos.col * 2;
  px_pos.x = (float)map_pos.col * map_px;
  px_pos.y = (float)map_pos.row * map_px;
  end_px_pos = px_pos;
}
Class_Unit::~Class_Unit() {}

/***********
Set系列函数
***********/
void Class_Unit::SetXYPos(const Pos_XY &px_pos) {
  this->px_pos = px_pos;
}
void Class_Unit::SetEndXYPos(const Pos_XY &end_px_pos) {
  this->end_px_pos = end_px_pos;
}
void Class_Unit::SetMapPos(const Pos_RC &map_pos) {
  this->map_pos = map_pos;
}
void Class_Unit::SetUnitPos(const Pos_RC &unit_pos) {
  this->unit_pos = unit_pos;
  //更新绘图终点
  end_px_pos.x = (float)unit_pos.col * half_map_px;
  end_px_pos.y = (float)unit_pos.row * half_map_px;

  //px_pos = end_px_pos;//测试用语句，补帧完成后删除
}
void Class_Unit::SetDirection(Direction newDirection) {
  direction = newDirection;
}
void Class_Unit::SetArmorLev(Armor newArmorLev) {
  Armor_Level = newArmorLev;
}

/**********
Get系列函数
**********/
const Pos_XY &Class_Unit::GetXYPos()const {
  return px_pos;
}
const Pos_XY &Class_Unit::GetEndXYPos() const {
  return end_px_pos;
}
const UnitType &Class_Unit::GetType()const {
  return type;
}
const Pos_RC &Class_Unit::GetMapPos() const {
  return map_pos;
}
const Pos_RC &Class_Unit::GetUnitPos() const {
  return unit_pos;
}
const Direction &Class_Unit::GetDirection()const {
  return direction;
}
const Armor &Class_Unit::GetArmorLev()const {
  return Armor_Level;
}
float Class_Unit::GetSpeed() const {
  //默认基类返回0，具体取值由各继承类完成
  return 0;
}
