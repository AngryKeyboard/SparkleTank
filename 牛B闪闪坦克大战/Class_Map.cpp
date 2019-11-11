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
#include "Class_Map.h"

Class_Map::Class_Map() {
  for (size_t i = 0; i < MapFileCount; i++) {
    loadimage(map_pic + i, Map_FileName[i]);//加载图片文件
  }
  loadmap();
}

void Class_Map::loadmap(unsigned int stage) {
  ifstream map_file;//地图文件流
  wstring temp;//保存地图文件名

  temp = map_file_path;
  temp += map_file_name;
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
}

void Class_Map::show()const {
  for (int row = 0; row < map_row; row++) {
    for (int col = 0; col < map_col; col++) {
      MapInt temp = map[row][col];
      switch (temp)//根据地形绘图
      {
        case WALL:
          putimage(col * map_px, row * map_px, map_pic + FileNum_wall);
          break;
        case IRON:
          putimage(col * map_px, row * map_px, map_pic + FileNum_iron);
          break;
        case BORDER:
          putimage(col * map_px, row * map_px, map_pic + FileNum_border);
          break;
        case SEA:
          putimage(col * map_px, row * map_px, map_pic + FileNum_sea0);
          break;
        case ICE:
          putimage(col * map_px, row * map_px, map_pic + FileNum_ice);
          break;
        case JUNGLE:
          putimage(col * map_px, row * map_px, map_pic + FileNum_jungle);
          break;
        default:
          break;
      }
      if (temp<WALL && temp>EMPTY)//绘制残缺的砖块
      {
        putimage(col * map_px, row * map_px, map_pic + FileNum_wall);//先绘制完整的砖块
        //for (size_t i = 0; i < 2; i++)//检查上半边砖块是否残缺
        //{
        //  if ((temp & 1) == 0)//如果末位为0
        //  {
        //    //计算要擦除的边界
        //    int left = col * map_px + i * half_map_px;
        //    int top = row * map_px;
        //    int right = col * map_px + (i + 1) * half_map_px;
        //    int bottom = row * map_px + half_map_px;
        //    clearrectangle(left, top, right, bottom);//擦除相应区域
        //  }
        //  temp = temp >> 1;//右移一位
        //}
        //for (size_t i = 0; i < 2; i++)//检查下半边砖块是否残缺
        //{
        //  if ((temp & 1) == 0)//如果末位为0
        //  {
        //    //计算要擦除的边界
        //    int left = col * map_px + i * half_map_px;
        //    int top = row * map_px + half_map_px;
        //    int right = col * map_px + (i + 1) * half_map_px;
        //    int bottom = row * map_px + map_px;
        //    clearrectangle(left, top, right, bottom);//擦除相应区域
        //  }
        //  temp = temp >> 1;//右移一位
        //}

        //检查砖块是否残缺（一个完整砖块看作两行两列）
        for (int s_row = 0; s_row < 2; s_row++) {
          for (int s_col = 0; s_col < 2; s_col++) {
            if ((temp & 1) == 0)//如果末位为0
            {
              //计算要擦除的边界
              int left = col * map_px + s_col * half_map_px;
              int top = row * map_px + s_row * half_map_px;
              int right = col * map_px + (s_col + 1) * half_map_px;
              int bottom = row * map_px + (s_row + 1) * half_map_px;
              clearrectangle(left, top, right, bottom);//擦除相应区域
            }
            temp = temp >> 1;//右移一位
          }
        }
      }
    }
  }
}
