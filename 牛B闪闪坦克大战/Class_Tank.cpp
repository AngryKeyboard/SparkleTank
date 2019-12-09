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


Class_Tank::Class_Tank(Pos_RC map_pos, UnitType type, Direction dir, Armor Lev)
  : Class_Unit(map_pos, type, dir), trackState(false) {
  timer_trackState = timeGetTime();
  SetArmorLev(Lev);
}

/**********
Get系列函数
**********/
bool Class_Tank::GetTrackState() const {
  return trackState;
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
  DWORD now = timeGetTime();//调用此函数时的时间

  //如果到了转换周期，就切换履带显示
  if (now - timer_trackState >= renewClock) {
    timer_trackState = now;
    trackState = !trackState;
  }
}
