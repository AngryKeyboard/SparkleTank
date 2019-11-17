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
#include <iostream>
#include <Windows.h>
#include <Mmsystem.h>
#include <conio.h>
#include <mmsystem.h>
#include <graphics.h>

#pragma comment(lib,"Winmm.lib")

using namespace std;

//特殊宏定义
#define Int unsigned short
#define MapInt unsigned char
#define KEY_DOWN(VK_NONAME) (GetAsyncKeyState(VK_NONAME) & 0x8000)

//绘图坐标
typedef struct {
  short x, y;
}Pos_XY;

/*****************
设置窗口的相关参数
*****************/
const Int source_map_px = 8;//原坦克大战一个地图单元对应的像素大小
const Int px_multiple = 2;//图片像素放大倍数
const Int map_px = px_multiple * source_map_px;//每个地图单元的实际像素大小
const Int unit_px = map_px * 2;//坦克、道具的绘图大小
const Int half_map_px = map_px / 2;//子弹绘图大小
//地图数组的行、列数
const Int map_row = 30;
const Int map_col = 32;
//单元数组的行、列数，为地图数组的两倍，以此达到坦克等移动“半格”的效果
const Int unit_row = map_row * 2;
const Int unit_col = map_col * 2;

//游戏界面的宽和高（像素）
const Int map_wide = map_px * map_col;
const Int map_height = map_px * map_row;
//菜单按钮的宽和高
const Int menue_wide = 80;
const Int menue_height = 40;
//菜单文字的宽度和高度、字体类型
const Int text_size = 30;
const wchar_t *const text_style = _T("华文楷体");


const Int unit_size = 4;//每个单元在unit矩阵中占用的宽度（坦克长宽为4，炮弹为2）
const Int bullet_size = unit_size / 2;
const Int unit_sizeInMap = unit_size / 2;

/*******************************
物体移动速度、画面刷新速率等设置
*******************************/
const Int RenewClock = 1000 / 60;//画面刷新周期
enum Speed//每次刷新时物体应移动的像素数
{
  SlowSpeed = (2 * unit_sizeInMap * map_px) * RenewClock / 1000, //每秒走两大格
  NormalSpeed = (3 * unit_sizeInMap * map_px) * RenewClock / 1000, //每秒走三大格
  FastSpeed = (4 * unit_sizeInMap * map_px) * RenewClock / 1000,//每秒走四大格
  HighSpeed = 2 * FastSpeed,
  VeryHighSpeed = 2 * HighSpeed
};

/***************
各单位的相关参数
***************/
enum MapType//地图类型
{
  EMPTY,//空地
  WALL_UL = 0x01, WALL_UR = 0x02, WALL_DL = 0x04, WALL_DR = 0x08,//四分之一块砖
  WALL_UP = 0x03, WALL_LEFT = 0x05, WALL_RIGHT = 0x0A, WALL_DOWN = 0x0C,//半块砖
  WALL = 0x0F,//砖墙
  IRON,//防爆门
  BORDER,//地图边界
  SEA,//海面
  ICE = 0x21,//冰面
  JUNGLE,//丛林
};
enum UnitType//各单位类型值，用于碰撞检测
{
  //子弹
  BULLET = 500,
  P1 = 300,//1号玩家
  P2 = 400,//2号玩家
  CP = 600,//敌人
  COMMANDER = 0xC8,//指挥官
};
enum Direction//方向，绘制、开炮时用
{
  UP, LEFT, DOWN, RIGHT, DirectionCount
};
enum Armor//坦克装甲等级
{
  DEAD = -1, NORMAL, LIGHT, STRONG, HEAVY, ArmorCount
};
enum Key//键盘控制
{
  Key_UP = 'W', Key_LEFT = 'A', Key_RIGHT = 'D', Key_DOWN = 'S',
  Key_SHOOT = 'J', Key_PAUSE = 'P',
  Key_START = 'F', Key_SELECT = 'R'
};

/*************
玩家图片文件名
**************/
const wchar_t *const Commander_FileName[2] = { _T("Image\\commander0.png"),_T("Image\\commander1.png") };
const wchar_t *const CommanderHide_FileName[2] = { _T("Image\\commander0_hide.png"),_T("Image\\commander1_hide.png") };


/********************
地图元素的图片文件名
********************/
enum MapFileNum {
  FileNum_wall, FileNum_iron, FileNum_border, FileNum_sea0, FileNum_sea1, FileNum_ice, FileNum_jungle, MapFileCount
};
const wchar_t *const Map_FileName[MapFileCount] =
{ _T("Image\\map\\wall.png"),_T("Image\\map\\iron.png"),_T("Image\\map\\border.png"),_T("Image\\map\\sea0.png"),_T("Image\\map\\sea1.png"),_T("Image\\map\\ice.png"),_T("Image\\map\\jungle.png") };

//子弹图片文件名
const wchar_t *const Bullet_FileName[DirectionCount] =
{ _T("Image\\bullet\\bullet_up.png"),_T("Image\\bullet\\bullet_left.png"),_T("Image\\bullet\\bullet_down.png"),_T("Image\\bullet\\bullet_right.png") };
const wchar_t *const BulletHide_FileName[DirectionCount] =
{ _T("Image\\bullet\\bullet_hide_up.png"),_T("Image\\bullet\\bullet_hide_left.png"),_T("Image\\bullet\\bullet_hide_down.png"),_T("Image\\bullet\\bullet_hide_right.png") };

//爆炸图片文件名
const wchar_t *const Boom_FileName[5] =
{ _T("Image\\boom\\boom0.png"),_T("Image\\boom\\boom1.png") ,_T("Image\\boom\\boom2.png") ,_T("Image\\boom\\boom3.png") ,_T("Image\\boom\\boom4.png") };
const wchar_t *const BoomHide_FileName[5] =
{ _T("Image\\boom\\boom0_hide.png"),_T("Image\\boom\\boom1_hide.png") ,_T("Image\\boom\\boom2_hide.png") ,_T("Image\\boom\\boom3_hide.png") ,_T("Image\\boom\\boom4_hide.png") };
