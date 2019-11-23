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
#include "Class_GameWindow.h"

//void ctrl(Class_Tank& tank, Class_Map& map);//控制函数

int main() {
  Class_GameWindow game;
  game.play();
  //Class_GamePic pictures;
  //Class_Map map;
  //Class_Player P1;
  //Class_Bullet bullet;

  //BeginBatchDraw();//开启批量绘图模式
  ////bullet.shoot(P1);
  //while (true)
  //{
  //  static DWORD pic_timer = timeGetTime();//控制图像刷新时间
  //  DWORD now = timeGetTime();
  //  //如果到了刷新画面的时间，就执行绘制操作
  //  if (now - pic_timer >= RenewClock)
  //  {
  //    pic_timer = now;
  //    if (P1.renewXYPos())
  //    {
  //      //bullet.shoot(P1);
  //      ctrl(P1, map);
  //    }
  //    pictures.renewPic(map, P1,bullet);
  //    FlushBatchDraw();//刷新画面
  //  }

  //  Sleep(5);
  //}
  //EndBatchDraw();//结束批量绘图模式

  return 0;
}

//void ctrl(Class_Tank& tank, Class_Map& map)
//{
//  //当有多个按键按下时，坦克不移动（按键锁定，只允许一个方向移动）
//
//  bool key_state[DirectionCount] = { false };//保存当前按键状态
//  int count = 0;//保存当前按下按键的个数
//
//  //记录按键状态
//  if (KEY_DOWN(Key_DOWN))
//  {
//    key_state[DOWN] = true;
//  }
//  if (KEY_DOWN(Key_UP))
//  {
//    key_state[UP] = true;
//  }
//  if (KEY_DOWN(Key_LEFT))
//  {
//    key_state[LEFT] = true;
//  }
//  if (KEY_DOWN(Key_RIGHT))
//  {
//    key_state[RIGHT] = true;
//  }
//
//  //统计有几个键按下
//  for (size_t i = 0; i < DirectionCount; i++)
//  {
//    if (key_state[i])
//    {
//      count++;
//    }
//  }
//  if (count == 1)//如果只有一个键按下
//  {
//    size_t i;
//    for (i = 0; i < DirectionCount; i++)//找出被按下的键对应的方向
//    {
//      if (key_state[i] == true)
//      {
//        break;
//      }
//    }
//    tank.move((Direction)i, map);//坦克移动
//  }
//}
