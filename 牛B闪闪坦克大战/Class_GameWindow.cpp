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
#include "Class_GameWindow.h"
#include "Class_Timer.h"

Class_GameWindow::Class_GameWindow()
  :p1_bullet_count(0), game_state(false) {
  Class_Timer::initGameTimer();//初始化游戏时钟
}

void Class_GameWindow::gameWindow() {


  //进入游戏循环
  while (true) {

    //bool pause = false;

    //如果按下ESC，退出游戏
    if (KEY_DOWN(Key_ESC)) {
      HWND wnd = GetHWnd();
      int button = MessageBox(wnd, _T("确认退出游戏？"), _T("退出游戏"), MB_YESNO | MB_ICONQUESTION);
      if (button == IDYES) {
        break;
      }
      if (button == IDNO) {
        //点击取消会回到游戏，计时应重新开始（去掉中间暂停的时间）
        Class_Timer::renewSysClk();
      }
    }

    play();

    //使用游戏专用的延时函数，精准延时为每一帧的间隔
    Class_Timer::GameSleep(RenewClock);

  }
}

void Class_GameWindow::play() {
  Class_Unit *unit = &p1;//使用指针实现多态调用
  static DWORD pic_timer = Class_Timer::GetGameTime();//控制图像刷新时间
  DWORD now = Class_Timer::GetGameTime();

  if (game_state) {
    //检查暂停按钮
    if (KEY_DOWN(Key_PAUSE)) {
      HWND wnd = GetHWnd();
      int button = MessageBox(wnd, _T("继续游戏？"), _T("游戏暂停"), MB_RIGHT | MB_ICONINFORMATION);
      Class_Timer::renewSysClk();
    }

    //如果处于游戏状态，需要控制游戏中物体的刷新
    unit = &p1;
    if (unit) {
      if (unit->renewXYPos()) {
        //如果单位移动补帧完成，就进入控制状态
        ctrl(*unit, map);
      }

      for (size_t i = 0; i < enemys.size(); i++) {
        //刷新所有敌人移动状态
        if (enemys[i].renewXYPos()) {
          //如果坦克移动补帧完成，就进入控制状态
          enemys[i].renewRun(map);
        }
      }
    }
    renewBullets();
    renewStars();

    //测试语句（恶搞版），内有关卡切换、坦克形态切换
    static DWORD stage_timer = Class_Timer::GetGameTime();//控制关卡刷新时间
    now = Class_Timer::GetGameTime();
    if (now - stage_timer >= 3000) {
      stage_timer = now;

      map.ChangeStage(rand() % 35 + 1);
      unit->SetArmorLev((Armor)(rand() % ArmorCount));

      if (enemys.size() < MaxLivingEnemy && Class_ComputerPlayer::GetEnemyCount() > 0) {
        //如果剩余坦克大于0且场上还可以增加坦克，就创建一个敌军坦克
        //enemys.push_back(Class_ComputerPlayer());
        stars.push_back(Class_Star(CP_born_pos[(MaxEnemy - Class_ComputerPlayer::CP_count) % CP_born_pos_num], CP));
      }

      ////测试用，切换游戏状态
      //game_state = !game_state;
    }
  }
  else if (KEY_DOWN(Key_START) && !game_state) {
    //如果当前游戏没开始，且按下了游戏开始按钮，进入游戏
    game_state = !game_state;

    //游戏开场有3辆坦克
    for (size_t i = 0; i < 3; i++) {
      //enemys.push_back(Class_ComputerPlayer());
      stars.push_back(Class_Star(CP_born_pos[(MaxEnemy - Class_ComputerPlayer::CP_count) % CP_born_pos_num], CP));
    }
  }
  renewPic();//刷新画面
}

void Class_GameWindow::renewPic(bool effects) {
  //是否执行特效
  if (effects) {
    pictures.renewBkColor();//更新背景色
    pictures.renewEffects();//更新图片素材的颜色
  }

  cleardevice();//清屏
  //如果游戏没开始，绘制选择界面
  if (game_state == 0) {
    renewStartPic();
  }
  else {
    renewGamePic();
  }
  FlushBatchDraw();//显示到屏幕
}

void Class_GameWindow::renewGamePic() {
  pictures.drawMap(map.GetAVal());//绘制地图
  if (!bullets.empty())//绘制炮弹
  {
    for (size_t i = 0; i < bullets.size(); i++) {
      pictures.drawBullet(bullets[i]);
    }
  }
  if (!enemys.empty())//绘制敌军坦克
  {
    for (size_t i = 0; i < enemys.size(); i++) {
      pictures.drawTank(enemys[i]);
    }
  }
  pictures.drawTank(p1);//绘制坦克，测试阶段，以后改为循环访问，绘制所有坦克单位
  pictures.drawJungle(map.GetAVal());//绘制丛林
  pictures.drawBooms();//绘制爆炸贴图
  if (!stars.empty())//绘制星星
  {
    for (size_t i = 0; i < stars.size(); i++) {
      pictures.drawStar(stars[i].GetXYPos());
    }
  }
}

void Class_GameWindow::renewStartPic() {
  pictures.drawLogo();
}

void Class_GameWindow::renewBullets() {
  //for (size_t i = 0; i < bullets.size(); i++)
  //{
  //  if (bullets[i].renewXYPos())//如果补帧完成
  //  {
  //    //让子弹移动
  //    if (bullets[i].move(bullets[i].GetDirection(), map))//如果移动后有体积碰撞
  //    {
  //      if (bullets[i].GetOwner() == P1)
  //      {
  //        p1_bullet_count--;
  //      }
  //      //删除这枚炮弹
  //      bullets.erase(bullets.begin() + i);
  //      i--;//发生删除时，容器中的元素数量会变少
  //    }
  //  }
  //}
  if (!bullets.empty()) {
    for (auto it = bullets.begin(); it != bullets.end();) {
      bool flag = false;//暂用

      if (it->renewXYPos())//如果补帧完成
      {
        //暂用，功能正常后优化
        if (destroyTank(*it)) {
          if (it->GetOwner() == P1) {
            p1_bullet_count--;
          }
          flag = true;
        }

        //让炮弹移动
        if (it->move(it->GetDirection(), map))//如果移动后有体积碰撞
        {
          if (it->GetOwner() == P1) {
            p1_bullet_count--;
          }
          //修改地形、增加爆炸点，并且删除这枚炮弹
          destroyMap(*it);
          //pictures.addBoomPoint(it->GetBoomXYPos());
          //pictures.addBoomPoint(it->GetBoomXYPos(), true);//测试大型爆炸用
          //it = bullets.erase(it);
          //continue;
          flag = true;
        }

        if (flag) {
          pictures.addBoomPoint(it->GetBoomXYPos());
          it = bullets.erase(it);
          continue;
        }
      }
      it++;
    }
  }
}

void Class_GameWindow::renewStars() {
  if (!stars.empty()) {
    DWORD now = Class_Timer::GetGameTime();//获取当前游戏时间
    for (auto it = stars.begin(); it != stars.end();) {
      if (it->GetDuration() < now) {
        //如果当前星星已经过了持续时间，就清除掉该星星，并插入一个坦克对象
        //插入坦克
        if (it->GetType() == CP) {
          enemys.push_back(Class_ComputerPlayer(it->GetMapPos()));
        }

        it = stars.erase(it);//清除星星
        continue;
      }
      it++;
    }
  }
}

void Class_GameWindow::ctrl(Class_Unit &unit, Class_Map &map) {
  UnitType type = unit.GetType();
  if (type == P1 || type == CP)//该条件测试用
  {
    //当有多个按键按下时，坦克不移动（按键锁定，只允许一个方向移动）
    bool key_state[DirectionCount] = { false };//保存当前按键状态
    int count = 0;//保存当前按下按键的个数
    //记录按键状态
    if (KEY_DOWN(Key_DOWN)) {
      key_state[DOWN] = true;
    }
    if (KEY_DOWN(Key_UP)) {
      key_state[UP] = true;
    }
    if (KEY_DOWN(Key_LEFT)) {
      key_state[LEFT] = true;
    }
    if (KEY_DOWN(Key_RIGHT)) {
      key_state[RIGHT] = true;
    }
    //统计有几个键按下
    for (size_t i = 0; i < DirectionCount; i++) {
      if (key_state[i]) {
        count++;
      }
    }
    //如果只有一个键按下，移动坦克
    if (count == 1) {
      size_t i;
      for (i = 0; i < DirectionCount; i++)//找出被按下的键对应的方向
      {
        if (key_state[i] == true) {
          break;
        }
      }
      unit.move((Direction)i, map);//坦克移动
    }

    //控制炮弹发射
    if (KEY_DOWN(Key_SHOOT)) {
      const int shoot_cd = 100;//射击CD
      static DWORD shoot_timer = Class_Timer::GetGameTime() - shoot_cd;
      DWORD now = Class_Timer::GetGameTime();
      //static DWORD shoot_timer = timeGetTime() - shoot_cd;
      //DWORD now = timeGetTime();
      if (now - shoot_timer >= shoot_cd) {
        shoot_timer = now;
        shoot(unit);
      }
    }
  }
}

void Class_GameWindow::shoot(const Class_Unit &tank) {
  if (tank.GetType() == P1) {
    //玩家坦克，装甲等级低于LIGHT的时候，只能发射一枚炮弹
    if (tank.GetArmorLev() <= LIGHT) {
      if (p1_bullet_count >= normal_player_bullets) {
        //如果当前发射的炮弹数目已达上限，直接跳出
        return;
      }
    }
    else//更高装甲等级可以发射两枚炮弹
    {
      if (p1_bullet_count == max_player_bullets) {
        //如果当前发射的炮弹数目已达上限，直接跳出
        return;
      }
    }
    p1_bullet_count++;//记录炮弹数目
  }

  bullets.push_back(Class_Bullet(tank));//创建一个子弹到容器中
}

void Class_GameWindow::destroyMap(const Class_Bullet &bullet) {
  DestroyLev dLev = NoDestroy;
  unsigned int owner = bullet.GetOwner();
  Armor armorLev = bullet.GetArmorLev();
  Direction dir = bullet.GetDirection();

  const Pos_RC(*check_points_pos)[MapIndexCount] = bullet.GetCheckPointsPos();
  const MapInt(*check_points_val)[MapIndexCount] = bullet.GetCheckPointsVal();
  const bool(*touch_flags)[LayerCount][MapIndexCount] = bullet.GetTouchFlags();

  //如果碰撞点是边界，就直接退出这个函数
  if (map.GetVal((*check_points_pos)[0]) == BORDER) {
    return;
  }

  //根据坦克的阵营和火力等级，确定毁灭地形的程度
  if (owner == CP || owner == P1 && armorLev <= STRONG) {
    //如果坦克是敌军（或者玩家的火力较低），设置一次可以消除半块砖
    dLev = HalfDestroy;
  }
  else if (owner == P1 && armorLev == HEAVY) {
    dLev = AllDestroy;
  }

  //优化后的碰撞处理
  bool flag_1 = false;//标记第一层砖是否已经发生碰撞
  bool flag_headquarters = false;//记录指挥部是否被摧毁
  for (size_t iLayer = 0; iLayer < 2 && !flag_1; iLayer++)//用来区分砖块的两层
  {
    for (size_t iMap = 0; iMap < 2; iMap++)//用来区分两块砖
    {
      if ((*check_points_val)[iMap] > EMPTY && (*check_points_val)[iMap] <= BORDER) {
        if ((*touch_flags)[iLayer][iMap] == true) {
          flag_1 = true;//如果第一层就已经发生了碰撞，不会检查第二层砖
          map.DestroyMap((*check_points_pos)[iMap], dir, dLev);
        }
      }
      if (!flag_headquarters && (*check_points_val)[iMap] >= HEADQUARTERS_UL && (*check_points_val)[iMap] <= HEADQUARTERS_DR) {
        flag_headquarters = true;
        map.DestroyHeadquarters();//摧毁指挥部

        //添加一个大型爆炸
        Pos_XY boom_pos = { (float)(BossPos.col - 1) * map_px,(float)(BossPos.row - 1) * map_px };
        //增加一个坐标偏移，让爆炸点不会总是重合在一起
        int xy_offset[2] = { 0 };//获取一个坐标偏移量
        bool flag[2] = { false };//用来控制xy的坐标偏移采用加法还是减法
        for (size_t i = 0; i < 2; i++) {
          flag[i] = rand() % 2;
          xy_offset[i] = rand() % (source_map_px / 2) * px_multiple;
        }
        boom_pos.x += (float)pow(-1, flag[0]) * xy_offset[0];
        boom_pos.y += (float)pow(-1, flag[1]) * xy_offset[1];
        pictures.addBoomPoint(boom_pos, true);
      }
    }
  }
}

bool Class_GameWindow::destroyTank(const Class_Bullet &bullet) {
  unsigned int owner = bullet.GetOwner();
  Direction dir = bullet.GetDirection();
  Pos_RC check_points[2] = { bullet.GetUnitPos(),bullet.GetUnitPos() };
  bool flag = false;//保存碰撞结果

  //根据方向调整第二个检查点的坐标
  switch (dir) {
    case UP:
    case DOWN:
      check_points[1].col++;
      break;
    case LEFT:
    case RIGHT:
      check_points[1].row++;
      break;
    default:
      break;
  }

  //分别对两个检查点进行碰撞检测
  for (auto it = enemys.begin(); it != enemys.end();) {
    for (size_t i = 0; i < 2; i++) {
      Pos_RC enemy_pos = it->GetUnitPos();//获取当前敌人的坐标
      if (check_points[i].row >= enemy_pos.row && check_points[i].row <= enemy_pos.row + unit_size && check_points[i].col >= enemy_pos.col && check_points[i].col <= enemy_pos.col + unit_size) {
        //如果炮弹在坦克的体积范围内（如果炮弹击中了坦克）
        flag = true;
      }
    }
    if (flag) {
      //处理碰撞（消除被击中坦克）
      //注：所有坦克目前只需一炮就会被击毁
      pictures.addBoomPoint(it->GetBoomXYPos(), true);
      it = enemys.erase(it);
      break;
    }

    it++;
  }

  return flag;//返回碰撞结果，便于炮弹的消除处理
}
