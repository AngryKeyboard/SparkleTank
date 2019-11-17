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
#include <Windows.h>
#include "GameSettings.h"
#include "Class_GamePic.h"
#include "Class_Player.h"
#include "Class_Map.h"

int main() {
  Class_GamePic pictures;
  Class_Map map;
  Class_Player P1;

  //setbkcolor(GREEN);//测试用，设置背景色

  BeginBatchDraw();//开启批量绘图模式
  while (true) {
    Pos_XY pos = P1.GetPos();
    if (KEY_DOWN(Key_DOWN)) {
      pos.y++;//计算坐标
      //P1.SetPos(pos);//重写当前坐标
      P1.move(DOWN);
    }
    if (KEY_DOWN(Key_UP)) {
      pos.y--;//计算坐标
      //P1.SetPos(pos);//重写当前坐标
      P1.move(UP);
    }
    if (KEY_DOWN(Key_LEFT)) {
      pos.x--;//计算坐标
      //P1.SetPos(pos);//重写当前坐标
      P1.move(LEFT);
    }
    if (KEY_DOWN(Key_RIGHT)) {
      pos.x++;//计算坐标
      //P1.SetPos(pos);//重写当前坐标
      P1.move(RIGHT);
    }

    pictures.renewBkColor();//刷新背景色
    pictures.drawMap(map.GetAVal());
    pictures.drawTank(P1);
    FlushBatchDraw();//刷新画面

    Sleep(RenewClock);
  }
  EndBatchDraw();//结束批量绘图模式

  return 0;
}
