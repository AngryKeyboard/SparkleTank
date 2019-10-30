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
#include "GameSettings.h"


class Class_Unit {
private:
  Pos_XY pos;//绘图坐标
  UnitType type;//单位类型

public:
  Class_Unit(Pos_XY pos_px, UnitType type);
  virtual ~Class_Unit();

  //设置绘图像素点坐标
  void SetPos(Pos_XY pos);

  //获取单位的基本信息
  Pos_XY GetPos()const;
  UnitType GetType()const;

  //因为每个单元所占的画面大小不相同，图片规模不同，所以声明为纯虚函数
  virtual void show() = 0;
};

/***********
Set系列函数
***********/
inline void Class_Unit::SetPos(Pos_XY pos) {
  this->pos = pos;
}
/**********
Get系列函数
**********/
inline Pos_XY Class_Unit::GetPos()const {
  return pos;
}

inline UnitType Class_Unit::GetType()const {
  return type;
}
