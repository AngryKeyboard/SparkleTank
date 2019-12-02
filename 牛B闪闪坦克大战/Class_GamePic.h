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
#include "Class_Bullet.h"

enum Camp//阵营
{
  CampPlayer, CampComputerPlayer, CampCount
};
enum MapFileNum//图片文件编号
{
  FileNum_wall, FileNum_iron, FileNum_border, FileNum_sea0, FileNum_sea1, FileNum_ice, FileNum_jungle, MapFileCount
};

//图片管理类
class Class_GamePic {
public:
  Class_GamePic();
  ~Class_GamePic();
  //绘制坦克
  void drawTank(const Class_Tank &tank);
  //绘制地图
  void drawMap(const MapInt(*map)[map_row][map_col]);
  //绘制丛林
  void drawJungle(const MapInt(*map)[map_row][map_col]);
  //绘制子弹
  void drawBullet(Class_Bullet &bullet);
  //平滑地变化背景色
  void renewBkColor();
  //转换所有图片的颜色
  void renewEffects();
  //刷新画面，effects表示是否启用特效
  //void renewPic(Class_Map& map, const Class_Tank& tank, Class_Bullet& bullet, bool effects = true);

protected:
  //透明贴图
  /*void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);*/
  //半透明贴图
  void half_transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
  //根据当前背景色，修改图片素材的颜色
  void changeEffects(IMAGE *dstimg, IMAGE *srcimg);
  //绘制海面（动态效果）
  void drawSea(int x, int y);


private:
  IMAGE tankPic[CampCount][ArmorCount][DirectionCount][2];//坦克图片，角标从左到右分别为：阵营、装甲等级、方向、履带切换
  IMAGE mapPic[MapFileCount];//地图图片
  IMAGE bulletPic[DirectionCount];//子弹图片

  //经过处理的图片素材
  IMAGE tankPic_effects[CampCount][ArmorCount][DirectionCount][2];
  IMAGE mapPic_effects[MapFileCount];
  IMAGE bulletPic_effects[DirectionCount];

  float bkHSL[3];//保存背景色HSL模型颜色数据
};
