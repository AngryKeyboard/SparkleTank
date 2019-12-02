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
#pragma once

#include <vector>
#include "GameSettings.h"
#include "Class_GamePic.h"
#include "Class_Player.h"
#include "Class_Map.h"
#include "Class_Bullet.h"

using std::vector;

const unsigned int max_player_bullets = 2;//玩家同时发射的子弹数量上限
const unsigned int normal_player_bullets = 1;

class Class_GameWindow {
private:
  Class_GamePic pictures;
  Class_Map map;
  Class_Player p1;
  //Class_Bullet* bullet;//测试阶段用
  vector<Class_Bullet> bullets;
  unsigned int p1_bullet_count;//记录1P发射的子弹数

public:
  Class_GameWindow();
  //开始游戏
  void play();

protected:
  //刷新画面，effects代表是否使用牛B闪闪特效
  void renewPic(bool effects = true);
  //控制函数，刷新子弹状态
  void renewBullets();
  //控制函数，传入其它可移动单位，也能让玩家进行控制
  void ctrl(Class_Unit &unit, Class_Map &map);//控制函数
  //射击
  void shoot(const Class_Unit &tank);
};
