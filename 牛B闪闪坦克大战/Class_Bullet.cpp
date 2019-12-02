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
#include "Class_Bullet.h"

Class_Bullet::Class_Bullet(const Class_Unit &tank)
  :Class_Unit(tank.GetMapPos(), BULLET, tank.GetDirection()), owner(tank.GetType()) {
  Pos_RC unit_pos = tank.GetUnitPos();//存储修正后的unit坐标
  Pos_XY px_pos = GetXYPos();//存储修正后的绘图坐标
  //修正子弹单位的坐标
  switch (GetDirection()) {
    case UP:
      unit_pos.col++;
      px_pos.x = unit_pos.col * half_map_px + half_map_px / 2;
      break;
    case LEFT:
      unit_pos.row++;
      px_pos.y = unit_pos.row * half_map_px + half_map_px / 2;
      break;
    case DOWN:
      unit_pos.col++;
      unit_pos.row += 3;
      px_pos.x = unit_pos.col * half_map_px + half_map_px / 2;
      px_pos.y = unit_pos.row * half_map_px + half_map_px / 2;
      break;
    case RIGHT:
      unit_pos.row++;
      unit_pos.col += 3;
      px_pos.x = unit_pos.col * half_map_px + half_map_px / 2;
      px_pos.y = unit_pos.row * half_map_px + half_map_px / 2;
      break;
    default:
      break;
  }
  SetUnitPos(unit_pos);
  SetXYPos(px_pos);
  unit_pos.row /= 2;
  unit_pos.col /= 2;
  SetMapPos(unit_pos);
  SetArmorLev(tank.GetArmorLev());
}

bool Class_Bullet::move(Direction dir, const Class_Map &map) {
  //获取子弹当前数据
  Pos_RC unit_pos = GetUnitPos();
  Pos_RC map_pos = GetMapPos();

  //根据移动方向修正一次map_pos
  switch (dir) {
    case UP:
      //map_pos.row = unit_pos.row / 2 + unit_pos.row % 2;
      map_pos.row = unit_pos.row / 2;
      break;
    case LEFT:
      //map_pos.col = unit_pos.col / 2 + unit_pos.col % 2;
      map_pos.col = unit_pos.col / 2;
      break;
    case DOWN:
      //map_pos.row = unit_pos.row / 2;
      map_pos.row = unit_pos.row / 2 - unit_pos.row % 2;
      break;
    case RIGHT:
      //map_pos.col = unit_pos.col / 2;
      map_pos.col = unit_pos.col / 2 - unit_pos.col % 2;
      break;
    default:
      break;
  }
  SetMapPos(map_pos);

  //开始移动
  switch (dir) {
    case UP:
      //SetDirection(UP);//修改单位朝向
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.row--;
      }
      break;
    case LEFT:
      //SetDirection(LEFT);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.col--;
      }
      break;
    case DOWN:
      //SetDirection(DOWN);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.row++;
      }
      break;
    case RIGHT:
      //SetDirection(RIGHT);
      if (!ifTouch(map))//如果没有发生碰撞
      {
        unit_pos.col++;
      }
      break;
    default:
      break;
  }
  if (unit_pos == GetUnitPos()) {
    //如果移动代码运行后，坐标和之前相等，说明发生了碰撞
    return true;
  }
  SetUnitPos(unit_pos);
  return false;
}

float Class_Bullet::GetSpeed() const {
  //区分玩家的子弹还是电脑玩家的子弹
  if (owner == CP) {
    //电脑玩家的子弹速度
    if (GetArmorLev() == STRONG) {
      return VeryHighSpeed / 1000.0f;
    }
    else {
      return HighSpeed / 1000.0f;
    }
  }
  else {
    //玩家的子弹速度
    if (GetArmorLev() == NORMAL) {
      return HighSpeed / 1000.0f;
    }
    else {
      return VeryHighSpeed / 1000.0f;
    }
  }
}

bool Class_Bullet::ifTouch(const Class_Map &map) const {
  Pos_RC curPos[2] = { GetMapPos(),GetMapPos() };//获取当前行列坐标，有两个碰撞判定点
  //计算需要进行体积碰撞判定的两个点
  switch (GetDirection()) {
    case UP:
      //curPos[0].row--;
      //curPos[1].row--;
      curPos[1].col++;
      break;
    case LEFT:
      //curPos[0].col--;
      //curPos[1].col--;
      curPos[1].row++;
      break;
    case DOWN:
      curPos[1].col++;
      break;
    case RIGHT:
      curPos[1].row++;
      break;
    default:
      break;
  }

  //碰撞判断
  for (size_t i = 0; i < 2; i++) {
    MapInt checkPoint = map.GetVal(curPos[i]);//获取需要检查的地图点取值
    if (checkPoint > EMPTY && checkPoint <= BORDER) {
      return true;//发生碰撞
    }
  }
  return false;//未发生碰撞
}

unsigned int Class_Bullet::GetOwner() {
  return owner;
}
