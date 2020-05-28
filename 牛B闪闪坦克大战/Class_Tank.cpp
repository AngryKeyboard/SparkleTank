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
#include "Class_Tank.h"
#include "Class_Timer.h"


Class_Tank::Class_Tank(Pos_RC map_pos, UnitType type, Direction dir, Armor Lev)
  : Class_Unit(map_pos, type, dir), trackState(false) {
  //timer_trackState = timeGetTime();
  timer_trackState = 0;
  SetArmorLev(Lev);
}

/**********
Get系列函数
**********/
bool Class_Tank::GetTrackState() const {
  return trackState;
}

Pos_XY Class_Tank::GetBoomXYPos() const {
  //根据终点绘图坐标得到一个爆炸贴图的绘图坐标
  Pos_XY tmp = GetEndXYPos();
  tmp.x -= 2 * half_map_px;
  tmp.y -= 2 * half_map_px;
  //增加一个坐标偏移，让爆炸点不会总是重合在一起
  int xy_offset[2] = { 0 };//获取一个坐标偏移量
  bool flag[2] = { false };//用来控制xy的坐标偏移采用加法还是减法
  for (size_t i = 0; i < 2; i++) {
    flag[i] = rand() % 2;
    xy_offset[i] = rand() % (source_map_px / 2) * px_multiple;
  }
  tmp.x += (float)pow(-1, flag[0]) * xy_offset[0];
  tmp.y += (float)pow(-1, flag[1]) * xy_offset[1];
  return tmp;
}

/********************
控制函数（坦克行走等）
********************/
bool Class_Tank::move(Direction dir, const Class_Map &map) {
  renewTrackState();//控制履带切换
  return Class_Unit::move(dir, map);
}

void Class_Tank::renewTrackState() {
  DWORD renewClock = (DWORD)(px_multiple / (GetSpeed() / RenewClock)); //求出履带切换周期（乱凑的数字）
  DWORD now = Class_Timer::GetGameTime();//调用此函数时的时间
  //DWORD now = timeGetTime();//调用此函数时的时间

  //如果到了转换周期，就切换履带显示
  if (now - timer_trackState >= renewClock) {
    timer_trackState = now;
    trackState = !trackState;
  }
}
