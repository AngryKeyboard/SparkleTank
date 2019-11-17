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
#include "GameSettings.h"
#include "Class_Tank.h"
#include "Class_Map.h"

enum Camp {
  CampPlayer, CampComputerPlayer, CampNum
};

class Class_GamePic {
public:
  Class_GamePic();
  ~Class_GamePic();
  //绘制坦克
  void drawTank(const Class_Tank &tank);
  //绘制地图
  void drawMap(const MapInt(*map)[map_row][map_col]);
  //平滑地变化背景色
  void renewBkColor();

protected:
  //透明贴图
  void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
  //半透明贴图
  void half_transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);

private:
  //保存所有坦克图片，变量从左到右分别为：敌军/我军坦克、装甲等级、方向、履带切换
  IMAGE tankPic[CampNum][ArmorCount][DirectionCount][2];

  //保存地图图片
  IMAGE mapPic[MapFileCount];
};
