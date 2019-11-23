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
void Class_Tank::move(Direction dir, const Class_Map &map) {
  renewTrackState();//控制履带切换

  //获取坦克当前数据
  Pos_RC unit_pos = GetUnitPos();
  Pos_RC map_pos = GetMapPos();
  Direction curDir = GetDirection();

  //90度转向时的调整，对齐地图坐标
  if ((dir - curDir) % 2) {
    switch (curDir) {
      case UP:
        if (unit_pos.row % 2) {
          unit_pos.row--;
        }
        break;
      case LEFT:
        if (unit_pos.col % 2) {
          unit_pos.col--;
        }
        break;
      case DOWN:
        if (unit_pos.row % 2) {
          unit_pos.row++;
        }
        break;
      case RIGHT:
        if (unit_pos.col % 2) {
          unit_pos.col++;
        }
        break;
      default:
        break;
    }
    map_pos.row = unit_pos.row / 2;
    map_pos.col = unit_pos.col / 2;
    SetUnitPos(unit_pos);
    SetMapPos(map_pos);
    SetXYPos(GetEndXYPos());
  }

  //根据移动方向修正一次map_pos
  switch (dir) {
    case UP:
      //修正半格地图对齐的碰撞监测点
      map_pos.row = unit_pos.row / 2 + unit_pos.row % 2;
      break;
    case LEFT:
      //修正半格地图对齐的碰撞监测点
      map_pos.col = unit_pos.col / 2 + unit_pos.col % 2;
      break;
    case DOWN:
      map_pos.row = unit_pos.row / 2;
      break;
    case RIGHT:
      map_pos.col = unit_pos.col / 2;
      break;
    default:
      break;
  }
  SetMapPos(map_pos);

  //开始移动
  switch (dir) {
    case UP:
      SetDirection(UP);//修改坦克朝向
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.row--;
      }
      break;
    case LEFT:
      SetDirection(LEFT);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.col--;
      }
      break;
    case DOWN:
      SetDirection(DOWN);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.row++;
      }
      break;
    case RIGHT:
      SetDirection(RIGHT);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.col++;
      }
      break;
    default:
      break;
  }
  SetUnitPos(unit_pos);

  //刷新一次map_pos，便于下一次移动时的碰撞检测
  switch (GetDirection()) {
    case UP:
      //修正半格地图对齐的碰撞监测点
      map_pos.row = unit_pos.row / 2 + unit_pos.row % 2;
      break;
    case LEFT:
      //修正半格地图对齐的碰撞监测点
      map_pos.col = unit_pos.col / 2 + unit_pos.col % 2;
      break;
    case DOWN:
      map_pos.row = unit_pos.row / 2;
      break;
    case RIGHT:
      map_pos.col = unit_pos.col / 2;
      break;
    default:
      break;
  }
  SetMapPos(map_pos);
}
bool Class_Tank::ifTouch(const Class_Map &map)const {
  Pos_RC curPos[2] = { GetMapPos(),GetMapPos() };//获取当前行列坐标，有两个碰撞判定点
  //计算需要进行体积碰撞判定的两个点
  switch (GetDirection()) {
    case UP:
      curPos[0].row--;
      curPos[1].row--;
      curPos[1].col++;
      break;
    case LEFT:
      curPos[0].col--;
      curPos[1].col--;
      curPos[1].row++;
      break;
    case DOWN:
      curPos[0].row += 2;
      curPos[1].row += 2;
      curPos[1].col++;
      break;
    case RIGHT:
      curPos[0].col += 2;
      curPos[1].col += 2;
      curPos[1].row++;
      break;
    default:
      break;
  }

  //碰撞判断
  for (size_t i = 0; i < 2; i++) {
    MapInt checkPoint = map.GetVal(curPos[i]);//获取需要检查的地图点取值
    if (checkPoint > EMPTY && checkPoint <= SEA) {
      return true;//发生碰撞
    }
  }
  return false;//未发生碰撞
}
bool Class_Tank::renewXYPos() {
  Pos_XY cur_pos = GetXYPos();
  Pos_XY end_pos = GetEndXYPos();
  float speed = GetSpeed();

  //根据方向和终点绘图坐标，判断是否刷新当前绘图坐标
  switch (GetDirection()) {
    case UP:
      if (cur_pos.y > end_pos.y) {
        cur_pos.y -= speed;
      }
      break;
    case LEFT:
      if (cur_pos.x > end_pos.x) {
        cur_pos.x -= speed;
      }
      break;
    case DOWN:
      if (cur_pos.y < end_pos.y) {
        cur_pos.y += speed;
      }
      break;
    case RIGHT:
      if (cur_pos.x < end_pos.x) {
        cur_pos.x += speed;
      }
      break;
    default:
      break;
  }
  SetXYPos(cur_pos);//刷新绘图坐标

  //根据情况确定返回值
  switch (GetDirection()) {
    case UP:
      if (cur_pos.y <= end_pos.y) {
        return true;
      }
      break;
    case LEFT:
      if (cur_pos.x <= end_pos.x) {
        return true;
      }
      break;
    case DOWN:
      if (cur_pos.y >= end_pos.y) {
        return true;
      }
      break;
    case RIGHT:
      if (cur_pos.x >= end_pos.x) {
        return true;
      }
      break;
    default:
      break;
  }

  return false;
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
