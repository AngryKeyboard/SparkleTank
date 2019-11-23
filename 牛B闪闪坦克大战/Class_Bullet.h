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
#include "Class_Tank.h"
class Class_Bullet :
  public Class_Unit {
public:
  Class_Bullet();
  ~Class_Bullet();

  void changeState(bool fix = false);
  void SetSpeed(Speed);
  void SetLev(Armor);
  //发射子弹
  void shoot(const Class_Tank &tank);
  //子弹向前移动一步
  virtual void move(Direction dir, const Class_Map &map);

  bool GetState()const;
  float GetSpeed()const;
  Armor GetLev()const;

  bool ifMoveFinish();
  void checkHitWall(Class_Map &Map, UnitType TankType);//检查并处理地形碰撞

private:
  Pos_XY fix(Pos_XY pos);//修正绘图坐标

  bool state;//子弹状态，false为不存在，true为存在
  Speed speed;
  Armor lev;//子弹发射时候坦克的等级
};
