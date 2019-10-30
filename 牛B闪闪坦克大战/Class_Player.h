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
class Class_Player :
  public Class_Tank {
private:
  IMAGE img[ArmorCount][DirectionCount][2];//保存坦克的四种形态、四个方向的图片
  IMAGE img_hide[ArmorCount][DirectionCount];//保存坦克的蒙板，用于冰面上的透明显示
  void laod();//加载图片到内存的函数

public:
  Class_Player(Pos_XY pos_px = { 0,0 }, UnitType typ = P1, Direction dir = UP, Armor Lev = NORMAL);
  //绘图
  virtual void show();
};
