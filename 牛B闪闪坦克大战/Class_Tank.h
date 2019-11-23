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

//坦克基类，向下派生玩家坦克和电脑玩家坦克
class Class_Tank :
  public Class_Unit {
private:
  bool trackState;//切换履带显示
  DWORD timer_trackState;//记录履带切换时的时间点

public:
  Class_Tank(Pos_RC map_pos, UnitType type, Direction dir = DOWN, Armor Lev = NORMAL);

  /**********
  Get系列函数
  **********/
  //获取履带状态
  bool GetTrackState()const;

  /********************
  控制函数（坦克行走等）
  ********************/
  //坦克移动
  virtual void move(Direction dir, const Class_Map &map);
  //判断坦克是否发生碰撞，false代表无碰撞，true表示碰撞
  bool ifTouch(const Class_Map &map)const;
  //刷新坦克绘图坐标，返回true代表坦克可以接受控制
  bool renewXYPos();
  //切换履带显示，flag表示是否接收到切换信号，true表示需要切换
  void renewTrackState();
};
