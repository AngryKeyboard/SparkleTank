﻿/****************************************************************************************
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
#include "Class_ComputerPlayer.h"
#include "Class_Map.h"
#include "Class_Bullet.h"
#include "Class_Timer.h"
#include "Class_Star.h"

using std::vector;

const unsigned int max_player_bullets = 2;//玩家同时发射的子弹数量上限
const unsigned int normal_player_bullets = 1;
//const unsigned int max_player_bullets = 6;//玩家同时发射的子弹数量上限（翻倍畅玩版）
//const unsigned int normal_player_bullets = 3;

class Class_GameWindow {
private:
  Class_GamePic pictures;//图形对象，管理所有的图片绘制
  Class_Map map;//地图
  Class_Player p1;
  vector<Class_ComputerPlayer> enemys;//保存所有的敌军坦克
  vector<Class_Bullet> bullets;//保存所有的子弹
  vector<Class_Star> stars;//保存所有的星星
  unsigned int p1_bullet_count;//记录1P已经发射的炮弹数

  int game_state;//游戏状态（1代表正在游戏中，0代表游戏未开始）

public:
  Class_GameWindow();

  //进入游戏窗口的循环
  void gameWindow();
  //刷新游戏
  void play();

protected:
  //刷新画面，effects代表是否使用牛B闪闪特效
  void renewPic(bool effects = true);
  //刷新游戏游玩界面（玩游戏时使用）
  void renewGamePic();
  //刷新游戏开始界面
  void renewStartPic();
  //刷新子弹状态
  void renewBullets();
  //刷新星星的状态
  void renewStars();
  //控制函数，传入其它可移动单位，也能让玩家进行控制
  void ctrl(Class_Unit &unit, Class_Map &map);
  //射击
  void shoot(const Class_Unit &tank);
  //改变地形
  void destroyMap(const Class_Bullet &bullet);
  //击毁坦克
  bool destroyTank(const Class_Bullet &bullet);
};
