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
#include "Class_GamePic.h"

Class_GamePic::Class_GamePic() {
  initgraph(map_wide, map_height);//初始化绘图界面
  //坦克文件的路径名
  const wchar_t tank_file_path[] = _T(".\\Image\\tank\\");

  //阵营
  const wstring str_camp[] = { _T("player"),_T("enemy") };

  //方向
  const wstring str_dir[] = { _T("up"),_T("left"),_T("down"),_T("right") };

  //加载坦克图片文件
  for (size_t camp = 0; camp < CampNum; camp++)//控制阵营
  {
    for (int armor = 0; armor < ArmorCount; armor++)//控制装甲等级
    {
      for (size_t dir = 0; dir < DirectionCount; dir++)//控制方向
      {
        for (int run_state = 0; run_state < 2; run_state++)//控制履带的动态效果
        {
          //得到每个图片的路径和文件名
          wchar_t tmp[128] = { 0 };
          swprintf(tmp, _T("%s%s\\%s%d_%s%d.png"), tank_file_path, str_camp[camp].c_str(), str_camp[camp].c_str(), armor, str_dir[dir].c_str(), run_state);
          //加载图片文件到内存中
          loadimage(&tankPic[camp][armor][dir][run_state], tmp, unit_px, unit_px);
        }
      }
    }
  }

  for (size_t i = 0; i < MapFileCount; i++)//加载地图图片文件
  {
    loadimage(mapPic + i, Map_FileName[i], map_px, map_px);
  }
}

Class_GamePic::~Class_GamePic() {
  closegraph();//关闭绘图界面
}

void Class_GamePic::drawTank(const Class_Tank &tank) {
  Pos_XY pos = tank.GetPos();
  UnitType type = tank.GetType();
  Armor armor = tank.GetArmorLev();
  Direction dir = tank.GetDirection();
  Camp camp = type == CP ? CampComputerPlayer : CampPlayer;//根据单位类型得出阵营
  //putimage(pos.x, pos.y, &tankPic[camp][armor][dir][0]);//调试阶段，履带动态特效未实现，且不能透明贴图
  //transparentimage(NULL, pos.x, pos.y, &tankPic[camp][armor][dir][0]);
  half_transparentimage(NULL, pos.x, pos.y, &tankPic[camp][armor][dir][0]);
}

// 透明贴图函数
// 参数：
//    dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//    x, y: 目标贴图位置
//    srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//    transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
void Class_GamePic::transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg) {
  // 变量初始化
  DWORD *dst = GetImageBuffer(dstimg);
  DWORD *src = GetImageBuffer(srcimg);
  int src_width = srcimg->getwidth();
  int src_height = srcimg->getheight();
  int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
  int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

  // 计算贴图的实际长宽
  int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
  int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;

  // 修正贴图起始位置
  dst += dst_width * y + x;

  // 实现透明贴图
  for (int iy = 0; iy < iheight; iy++) {
    for (int ix = 0; ix < iwidth; ix++) {
      if ((src[ix] & 0xff000000))//绘制透明度不等于0的像素（非半透明绘图，有些地方图片可能失真，呈现黑色）
        //if ((src[ix] & 0xff000000) == 0xff000000)//只绘制透明度为0的像素（非半透明绘图，有些区域可能被扣除，变成背景色）
        dst[ix] = src[ix];
    }
    dst += dst_width;
    src += src_width;
  }
}

// 半透明贴图函数
// 参数：
//    dstimg：目标 IMAGE（NULL 表示默认窗体）
//    x, y: 目标贴图位置
//    srcimg: 源 IMAGE 对象指针
void Class_GamePic::half_transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg) {
  // 变量初始化
  DWORD *dst = GetImageBuffer(dstimg);
  DWORD *src = GetImageBuffer(srcimg);
  int src_width = srcimg->getwidth();
  int src_height = srcimg->getheight();
  int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
  int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

  // 计算贴图的实际长宽
  int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;   // 处理超出右边界
  int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;  // 处理超出下边界
  if (x < 0) {
    src += -x;       iwidth -= -x; x = 0;
  }        // 处理超出左边界
  if (y < 0) {
    src += src_width * -y; iheight -= -y;  y = 0;
  }        // 处理超出上边界

// 修正贴图起始位置
  dst += dst_width * y + x;

  // 实现透明贴图
  for (int iy = 0; iy < iheight; iy++) {
    for (int ix = 0; ix < iwidth; ix++) {
      int sa = ((src[ix] & 0xff000000) >> 24);
      int sr = ((src[ix] & 0xff0000) >> 16);  // 源值已经乘过了透明系数
      int sg = ((src[ix] & 0xff00) >> 8);   // 源值已经乘过了透明系数
      int sb = src[ix] & 0xff;        // 源值已经乘过了透明系数
      int dr = ((dst[ix] & 0xff0000) >> 16);
      int dg = ((dst[ix] & 0xff00) >> 8);
      int db = dst[ix] & 0xff;

      dst[ix] = ((sr + dr * (255 - sa) / 255) << 16)
        | ((sg + dg * (255 - sa) / 255) << 8)
        | (sb + db * (255 - sa) / 255);
    }
    dst += dst_width;
    src += src_width;
  }
}

void Class_GamePic::drawMap(const MapInt(*map)[map_row][map_col]) {
  for (int row = 0; row < map_row; row++) {
    for (int col = 0; col < map_col; col++) {
      MapInt temp = (*map)[row][col];
      switch (temp)//根据地形绘图
      {
        case WALL:
          putimage(col * map_px, row * map_px, mapPic + FileNum_wall);
          break;
        case IRON:
          putimage(col * map_px, row * map_px, mapPic + FileNum_iron);
          break;
        case BORDER:
          putimage(col * map_px, row * map_px, mapPic + FileNum_border);
          break;
        case SEA:
          putimage(col * map_px, row * map_px, mapPic + FileNum_sea0);
          break;
        case ICE:
          putimage(col * map_px, row * map_px, mapPic + FileNum_ice);
          break;
        case JUNGLE:
          //putimage(col * map_px, row * map_px, mapPic + FileNum_jungle);//非透明贴图，草丛有四个角落是黑色
          half_transparentimage(NULL, col * map_px, row * map_px, mapPic + FileNum_jungle);
          break;
        default:
          break;
      }
      if (temp<WALL && temp>EMPTY)//绘制残缺的砖块
      {
        putimage(col * map_px, row * map_px, mapPic + FileNum_wall);//先绘制完整的砖块

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

void Class_GamePic::renewBkColor() {
  const int step = 4;//颜色变化的步长上限
  static unsigned char color[3] = { 0 };//保存RGB颜色数据
  unsigned char increment[3];//保存RGB色的增量
  static bool flag[3] = { 0 };//控制颜色是加还是减，0加，1减

  int tmp = step;
  for (size_t i = 0; i < 3; i++) {
    //控制颜色的增量
    //increment[i] = rand() % step;//黑白切换
    increment[i] = rand() % tmp;
    tmp -= increment[i];
  }
  for (size_t i = 0; i < 3; i++) {
    int color_tmp = color[i] + pow(-1, flag[i]) * increment[i];
    if (color_tmp >= 256 || color_tmp < 0) {
      flag[i] = !flag[i];//翻转
    }
    color[i] += pow(-1, flag[i]) * increment[i];//修改RGB色的数据，flag控制颜色数值是减还是加
    //color[i] += flag[i] * increment[i];//修改RGB色的数据，flag控制颜色数值是否增加
  }
  setbkcolor(RGB(color[0], color[1], color[2]));

  cleardevice();//使用背景色清空屏幕
}
