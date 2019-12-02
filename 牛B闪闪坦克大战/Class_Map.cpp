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
#include <iostream>
#include <fstream>
#include "Class_Map.h"
using std::ifstream;
using std::wstring;
using std::hex;

Class_Map::Class_Map() {
  loadmap();
}

const MapInt(*Class_Map::GetAVal())[map_row][map_col]
{
  return &map;
}

MapInt Class_Map::GetVal(const Pos_RC &px_pos)const {
  return map[px_pos.row][px_pos.col];
}

void Class_Map::SetVal(const Pos_RC &px_pos, MapInt val) {
  map[px_pos.row][px_pos.col] = val;
}

void Class_Map::ChangeStage(unsigned int stage) {
  loadmap(stage);
}

void Class_Map::loadmap(unsigned int stage) {
  ifstream map_file;//地图文件流
  wstring temp;//保存地图文件名

  // 产生临时文件的文件名
  TCHAR tmp_map[_MAX_PATH];
  ::GetTempPath(_MAX_PATH, tmp_map);
  _tcscat(tmp_map, _T("map.txt"));
  // 将 MP3 资源提取为临时文件
  ExtractResource(tmp_map, _T("MAP"), _T("map"));

  //temp = map_file_path;
  //temp += map_file_name;
  temp = tmp_map;
  map_file.open(temp);
  if (!map_file.is_open()) {
    printf("地图文件打开失败！\n");
    exit(1);
  }

  //调整文件读取位置，如果玩家玩到35关以后，就从第一关地图开始
  stage -= 1;
  stage = stage % max_stage;
  map_file.seekg(stage * map_row * map_col * 3 + stage);//文件定位到指定字节（CRLF回车换行，所以要加stage）

  int num_temp;//暂存文件读取的整数，
  for (size_t row = 0; row < map_row; row++) {
    for (size_t col = 0; col < map_col; col++) {
      //map_file >> hex >> map[row][col];//无法正确读取一个整数
      map_file >> hex >> num_temp;
      map[row][col] = num_temp;
    }
  }
  map_file.close();

  // 删除临时文件
  DeleteFile(tmp_map);
}

//其它函数
//运算符重载
bool operator ==(const Pos_RC &a, const Pos_RC &b) {
  if (a.row == b.row && a.col == b.col) {
    return true;
  }
  return false;
}
