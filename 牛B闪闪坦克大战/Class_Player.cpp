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
  :Class_Tank(pos_px, typ, dir, Lev) {
  laod();
}

void Class_Player::show() {
  Pos_XY pos = GetPos();
  putimage(pos.x, pos.y, &img_hide[GetArmorLev()][GetDirection()], SRCAND);//先用遮罩和背景以“按位与”的方式绘制，得到黑色的待填充区域
  putimage(pos.x, pos.y, &img[GetArmorLev()][GetDirection()][0], SRCPAINT);//再用图片素材和背景以“按位或”的方式绘制，得到透明贴图效果
}

void Class_Player::laod() {
  for (int i = 0; i < ArmorCount; i++) {
    for (int j = 0; j < DirectionCount; j++) {
      for (size_t k = 0; k < 2; k++) {
        loadimage(&img[i][j][k], P1_FileName[i][j][k], unit_px, unit_px);
      }
    }
  }
  for (size_t i = 0; i < ArmorCount; i++) {
    for (size_t j = 0; j < DirectionCount; j++) {
      loadimage(&img_hide[i][j], PlayerHide_FileName[i][j], unit_px, unit_px);
    }
  }
}
