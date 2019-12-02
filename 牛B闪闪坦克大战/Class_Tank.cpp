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
//bool Class_Tank::ifTouch(const Class_Map& map)const
//{
//  Pos_RC curPos[2] = { GetMapPos(),GetMapPos() };//获取当前行列坐标，有两个碰撞判定点
//  //计算需要进行体积碰撞判定的两个点
//  switch (GetDirection())
//  {
//  case UP:
//    curPos[0].row--;
//    curPos[1].row--;
//    curPos[1].col++;
//    break;
//  case LEFT:
//    curPos[0].col--;
//    curPos[1].col--;
//    curPos[1].row++;
//    break;
//  case DOWN:
//    curPos[0].row += 2;
//    curPos[1].row += 2;
//    curPos[1].col++;
//    break;
//  case RIGHT:
//    curPos[0].col += 2;
//    curPos[1].col += 2;
//    curPos[1].row++;
//    break;
//  default:
//    break;
//  }
//
//  //碰撞判断
//  for (size_t i = 0; i < 2; i++)
//  {
//    MapInt checkPoint = map.GetVal(curPos[i]);//获取需要检查的地图点取值
//    if (checkPoint > EMPTY&& checkPoint <= SEA)
//    {
//      return true;//发生碰撞
//    }
//  }
//  return false;//未发生碰撞
//}
//bool Class_Tank::renewXYPos()
//{
//  Pos_XY cur_pos = GetXYPos();
//  Pos_XY end_pos = GetEndXYPos();
//  float speed = GetSpeed();
//
//  //根据方向和终点绘图坐标，判断是否刷新当前绘图坐标
//  switch (GetDirection())
//  {
//  case UP:
//    if (cur_pos.y > end_pos.y)
//    {
//      cur_pos.y -= speed;
//    }
//    break;
//  case LEFT:
//    if (cur_pos.x > end_pos.x)
//    {
//      cur_pos.x -= speed;
//    }
//    break;
//  case DOWN:
//    if (cur_pos.y < end_pos.y)
//    {
//      cur_pos.y += speed;
//    }
//    break;
//  case RIGHT:
//    if (cur_pos.x < end_pos.x)
//    {
//      cur_pos.x += speed;
//    }
//    break;
//  default:
//    break;
//  }
//  SetXYPos(cur_pos);//刷新绘图坐标
//
//  //根据情况确定返回值
//  switch (GetDirection())
//  {
//  case UP:
//    if (cur_pos.y <= end_pos.y)
//    {
//      return true;
//    }
//    break;
//  case LEFT:
//    if (cur_pos.x <= end_pos.x)
//    {
//      return true;
//    }
//    break;
//  case DOWN:
//    if (cur_pos.y >= end_pos.y)
//    {
//      return true;
//    }
//    break;
//  case RIGHT:
//    if (cur_pos.x >= end_pos.x)
//    {
//      return true;
//    }
//    break;
//  default:
//    break;
//  }
//
//  return false;
//}
void Class_Tank::renewTrackState() {
  DWORD renewClock = (DWORD)(px_multiple / (GetSpeed() / RenewClock)); //求出履带切换周期（乱凑的数字）
  DWORD now = timeGetTime();//调用此函数时的时间

  //如果到了转换周期，就切换履带显示
  if (now - timer_trackState >= renewClock) {
    timer_trackState = now;
    trackState = !trackState;
  }
}
