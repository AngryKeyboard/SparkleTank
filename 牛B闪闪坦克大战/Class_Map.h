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
#include <fstream>
#include "GameSettings.h"

const wchar_t map_file_path[] = _T("");//地图文件的路径名
const wchar_t map_file_name[] = _T("map.txt");//地图文件的文件名
const unsigned int max_stage = 35;//地图数量

//地图行列坐标
typedef struct {
  Int row, col;
}Pos_Map;

class Class_Map {
public:
  Class_Map();

  //const MapInt(* GetAVal()const)[map_row][map_col];//返回地图数组的首地址
  //笔记：上一行中第二个const表示成员函数为常成员函数，常成员函数返回指针时，会自动将指针转换为常指针；
  //    第一个const表示返回值为常量，所以第一个常声明必不可少，如果缺少第一个const，保留第二个const，程序编译在return处出错。

  const MapInt(*GetAVal())[map_row][map_col];//返回地图数组的首地址
  //笔记：上一行中，map_row和map_col必须和return处返回的二维数组行列一致，否则出错。若想增加函数的泛用性，考虑使用模板。
  MapInt GetVal(const Pos_Map &pos)const;//读取该行列的数值
  void SetVal(const Pos_Map &pos, MapInt val);//修改地图上的数值

private:
  MapInt map[map_row][map_col];//保存地图数据的数组
  void loadmap(unsigned int stage = 2);//读取地图数据，stage是关卡数
};
