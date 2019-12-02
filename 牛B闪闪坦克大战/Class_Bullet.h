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

class Class_Bullet :
  public Class_Unit {
public:
  Class_Bullet(const Class_Unit &tank);

  //子弹向前移动一步，如果发生地形碰撞，返回true
  virtual bool move(Direction dir, const Class_Map &map);
  //获取移动速度
  virtual float GetSpeed()const;
  //判断子弹是否发生碰撞，false代表无碰撞，true表示碰撞
  virtual bool ifTouch(const Class_Map &map)const;
  //获取子弹的所有者
  unsigned int GetOwner();

private:
  UnitType owner;//用来区分每一颗炮弹是谁发射的
};
