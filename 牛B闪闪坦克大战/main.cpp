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
#include "Class_Player.h"

int main() {
  Class_Player P1;

  initgraph(map_wide, map_height);
  setbkcolor(BLUE);//设置背景色
  cleardevice();//使用背景色清空屏幕

  BeginBatchDraw();
  while (true) {
    cleardevice();//使用背景色清空屏幕
    Pos_XY pos = P1.GetPos();
    if (KEY_DOWN(Key_DOWN)) {
      pos.y++;//计算坐标
      P1.SetPos(pos);//重写当前坐标
    }
    if (KEY_DOWN(Key_UP)) {
      pos.y--;//计算坐标
      P1.SetPos(pos);//重写当前坐标
    }
    if (KEY_DOWN(Key_LEFT)) {
      pos.x--;//计算坐标
      P1.SetPos(pos);//重写当前坐标
    }
    if (KEY_DOWN(Key_RIGHT)) {
      pos.x++;//计算坐标
      P1.SetPos(pos);//重写当前坐标
    }
    P1.show();//绘图
    FlushBatchDraw();
    Sleep(10);
  }
  EndBatchDraw();

  system("pause");
  return 0;
}
