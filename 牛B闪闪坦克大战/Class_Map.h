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

const unsigned int max_stage = 35;//地图数量

//行列坐标系
typedef struct {
  Int row, col;
}Pos_RC;
bool operator ==(const Pos_RC &a, const Pos_RC &b);

//地图类
class Class_Map {
public:
  Class_Map();

  //返回地图数组的首地址
  const MapInt(*GetAVal())[map_row][map_col];
  //返回指定地图行列的数值
  MapInt GetVal(const Pos_RC &px_pos)const;
  //修改地图上的数值
  void SetVal(const Pos_RC &px_pos, MapInt val);
  //切换关卡的函数
  void ChangeStage(unsigned int stage);

private:
  MapInt map[map_row][map_col];//保存地图数据的数组
  void loadmap(unsigned int stage = 29);//从文件读取地图数据，stage是关卡数
};
