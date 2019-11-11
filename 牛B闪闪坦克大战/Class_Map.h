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
  MapInt row, col;
}Pos_Map;

class Class_Map {
public:
  Class_Map();

  MapType GetVal(const Pos_Map &pos);//读取该行列的数值
  void SetVal(const Pos_Map &pos, MapType val);//修改地图上的数值
  void show()const;//显示地图

private:
  MapInt map[map_row][map_col];//保存地图数据的数组
  IMAGE map_pic[MapFileCount];//图片数组
  void loadmap(unsigned int stage = 1);//读取地图数据，stage是关卡数
};
