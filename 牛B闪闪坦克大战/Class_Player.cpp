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
#include "Class_Player.h"

Class_Player::Class_Player(Pos_XY pos_px, UnitType typ, Direction dir, Armor Lev)
  :Class_Tank(pos_px, typ, dir, Lev) {}


void Class_Player::move(Direction dir) {
  Pos_XY pos = GetPos();
  switch (dir) {
    case UP:
      SetDirection(UP);//修改坦克朝向
      pos.y -= NormalSpeed;//计算坦克新坐标
      break;
    case LEFT:
      SetDirection(LEFT);
      pos.x -= NormalSpeed;
      break;
    case DOWN:
      SetDirection(DOWN);
      pos.y += NormalSpeed;
      break;
    case RIGHT:
      SetDirection(RIGHT);
      pos.x += NormalSpeed;
      break;
    default:
      break;
  }
  SetPos(pos);
}
