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
#include "Class_GameWindow.h"

//void HpSleep(int ms);

Class_GameWindow::Class_GameWindow()
  :p1_bullet_count(0) {}

void Class_GameWindow::play() {
  Class_Unit *unit = &p1;//使用指针实现多态调用

  //bullet = new Class_Bullet(*unit);//测试用

  while (true) {
    static DWORD pic_timer = timeGetTime();//控制图像刷新时间
    DWORD now = timeGetTime();
    //如果到了刷新画面的时间，就执行绘制操作
    if (now - pic_timer >= RenewClock) {
      pic_timer = now;
      unit = &p1;
      if (unit) {
        if (unit->renewXYPos()) {
          ctrl(*unit, map);
        }
      }

      //测试用
      //unit = bullet;
      //if (unit)
      //{
      //  if (unit->renewXYPos())
      //  {
      //    ctrl(*unit, map);
      //  }
      //}
      renewBullets();
      renewPic();//刷新画面
    }
    Sleep(RenewClock / 3);

    //测试语句，测试关卡切换功能
    static DWORD stage_timer = timeGetTime();//控制关卡刷新时间
    now = timeGetTime();
    if (now - stage_timer >= 5000) {
      map.ChangeStage(rand() % 36);
      stage_timer = now;
    }
  }
}

void Class_GameWindow::renewPic(bool effects) {
  //是否执行特效
  if (effects) {
    pictures.renewBkColor();//更新背景色
    pictures.renewEffects();//更新图片素材的颜色
  }

  cleardevice();//清屏
  pictures.drawMap(map.GetAVal());//绘制地图
  if (!bullets.empty())//绘制子弹
  {
    for (size_t i = 0; i < bullets.size(); i++) {
      pictures.drawBullet(bullets[i]);
    }
  }
  pictures.drawTank(p1);//绘制坦克，测试阶段，以后改为循环访问，绘制所有坦克单位

  pictures.drawJungle(map.GetAVal());//绘制草丛
  FlushBatchDraw();//显示到屏幕
}

void Class_GameWindow::renewBullets() {
  for (size_t i = 0; i < bullets.size(); i++) {
    if (bullets[i].renewXYPos())//如果补帧完成
    {
      //让子弹移动
      if (bullets[i].move(bullets[i].GetDirection(), map))//如果移动后有体积碰撞
      {
        if (bullets[i].GetOwner() == P1) {
          p1_bullet_count--;
        }
        //删除这枚炮弹
        bullets.erase(bullets.begin() + i);
        i--;//发生删除时，容器中的元素数量会变少
      }
    }
  }
}

void Class_GameWindow::ctrl(Class_Unit &unit, Class_Map &map) {
  UnitType type = unit.GetType();
  if (type == P1 || type == CP)//该条件测试用
  {
    //当有多个按键按下时，坦克不移动（按键锁定，只允许一个方向移动）
    bool key_state[DirectionCount] = { false };//保存当前按键状态
    int count = 0;//保存当前按下按键的个数

    //记录按键状态
    if (KEY_DOWN(Key_DOWN)) {
      key_state[DOWN] = true;
    }
    if (KEY_DOWN(Key_UP)) {
      key_state[UP] = true;
    }
    if (KEY_DOWN(Key_LEFT)) {
      key_state[LEFT] = true;
    }
    if (KEY_DOWN(Key_RIGHT)) {
      key_state[RIGHT] = true;
    }

    //统计有几个键按下
    for (size_t i = 0; i < DirectionCount; i++) {
      if (key_state[i]) {
        count++;
      }
    }
    //如果只有一个键按下，移动坦克
    if (count == 1) {
      size_t i;
      for (i = 0; i < DirectionCount; i++)//找出被按下的键对应的方向
      {
        if (key_state[i] == true) {
          break;
        }
      }
      unit.move((Direction)i, map);//坦克移动
    }

    if (KEY_DOWN(Key_SHOOT)) {
      shoot(unit);
    }
  }
  //else if (type==BULLET)
  //{
  //  if (unit.move(unit.GetDirection(), map))
  //  {
  //    //delete bullet;
  //    //bullet = NULL;
  //  }
  //}
}

void Class_GameWindow::shoot(const Class_Unit &tank) {
  if (tank.GetType() == P1) {
    //玩家坦克，装甲等级低于LIGHT的时候，只能发射一枚炮弹
    if (tank.GetArmorLev() <= LIGHT) {
      if (p1_bullet_count >= normal_player_bullets) {
        //如果当前发射的炮弹数目已达上限，直接跳出
        return;
      }
    }
    else//更高装甲等级可以发射两枚炮弹
    {
      if (p1_bullet_count == max_player_bullets) {
        //如果当前发射的炮弹数目已达上限，直接跳出
        return;
      }
    }
    p1_bullet_count++;//记录炮弹数目
  }

  bullets.push_back(Class_Bullet(tank));//创建一个子弹到容器中
}

//void HpSleep(int ms)
//{
//  static clock_t oldclock = clock();    // 静态变量，记录上一次 tick
//
//  oldclock += ms * CLOCKS_PER_SEC / 1000; // 更新 tick
//
//  if (clock() > oldclock)         // 如果已经超时，无需延时
//    oldclock = clock();
//  else
//    while (clock() < oldclock)      // 延时
//      Sleep(1);           // 释放 CPU 控制权，降低 CPU 占用率
//}
