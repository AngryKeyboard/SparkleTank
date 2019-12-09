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
#include "Class_Tank.h"

const Pos_RC P1_born_pos = { 26,10 };
//const Pos_RC P1_born_pos = { 2,10 };//测试用

class Class_Player :
  public Class_Tank {
public:
  Class_Player(Pos_RC map_px = P1_born_pos, UnitType typ = P1, Direction dir = UP, Armor Lev = NORMAL);

  /**********
  Get系列函数
  **********/
  //获取移动速度
  virtual float GetSpeed()const;
};
