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
#include "Class_Bullet.h"

Class_Bullet::Class_Bullet()
  :Class_Unit({ 0, 0 }, BULLET), state(false) {
  //load();
}

Class_Bullet::~Class_Bullet() {}


void Class_Bullet::changeState(bool fix) {
  if (GetState())//如果子弹消失，新增一个小爆炸特效
  {
    Pos_XY pos = GetXYPos();
    pos.x = (short int)(pos.x - map_px * 1.75);
    pos.y = (short int)(pos.y - map_px * 1.75);
    if (fix) {
      switch (GetDirection()) {
        case UP:
          pos.y -= (short int)(map_px * 0.5);
          break;
        case LEFT:
          pos.x -= (short int)(map_px * 0.5);
          break;
        case DOWN:
          pos.y += (short int)(map_px * 0.5);
          break;
        case RIGHT:
          pos.x += (short int)(map_px * 0.5);
          break;
        default:
          break;
      }
    }
    //Class_Boom::addBoom(pos, false);
  }
  state = !state;
}

void Class_Bullet::SetSpeed(Speed speed) {
  this->speed = speed;
}

void Class_Bullet::SetLev(Armor lev) {
  this->lev = lev;
}

bool Class_Bullet::GetState()const {
  return state;
}

float Class_Bullet::GetSpeed()const {
  return speed;
}

Armor Class_Bullet::GetLev()const {
  return lev;
}


void Class_Bullet::shoot(const Class_Tank &tank) {
  Pos_RC unit_pos = tank.GetUnitPos();
  Direction direction = tank.GetDirection();
  Armor lev = tank.GetArmorLev();
  changeState();
  SetUnitPos(unit_pos);
  SetDirection(direction);
  SetLev(lev);
  if (lev >= LIGHT)//如果坦克装甲不是普通，子弹速度为最快
  {
    SetSpeed(VeryHighSpeed);
  }
  else {
    SetSpeed(HighSpeed);
  }
  SetMapPos({ unit_pos.row / 2U,unit_pos.col / 2U });
  SetXYPos(fix({ (float)unit_pos.col * half_map_px, (float)unit_pos.row * half_map_px }));
}

void Class_Bullet::move(Direction dir, const Class_Map &map) {
  if (!GetState() || !ifMoveFinish()) {
    return;
  }
  Pos_RC unit_pos = GetUnitPos();
  switch (GetDirection()) {
    case UP:
      unit_pos.row--;
      break;
    case LEFT:
      unit_pos.col--;
      break;
    case RIGHT:
      unit_pos.col++;
      break;
    case DOWN:
      unit_pos.row++;
      break;
    default:
      break;
  }
  SetUnitPos(unit_pos);
  SetMapPos({ unit_pos.row / 2U,unit_pos.col / 2U });
}

//void Class_Bullet::show()
//{
//  if (GetState())//子弹存在
//  {
//    Pos_XY pos = GetXYPos();
//    if (!ifMoveFinish())//如果没有移动完成，重新设置一下绘图坐标
//    {
//      switch (GetDirection())
//      {
//      case UP:
//        pos.y -= GetSpeed();
//        break;
//      case LEFT:
//        pos.x -= GetSpeed();
//        break;
//      case DOWN:
//        pos.y += GetSpeed();
//        break;
//      case RIGHT:
//        pos.x += GetSpeed();
//        break;
//      default:
//        break;
//      }
//      SetXYPos(pos);
//    }
//    else
//    {
//      move();
//    }
//    putimage(GetXYPos().x, GetXYPos().y, &img_hide[GetDirection()], SRCAND);
//    putimage(GetXYPos().x, GetXYPos().y, &img[GetDirection()], SRCPAINT);
//  }
//}

//void Class_Bullet::load()
//{
//  static bool load = false;
//  if (!load)
//  {
//    for (size_t i = 0; i < DirectionCount; i++)
//    {
//      loadimage(&img[i], Bullet_FileName[i], map_px / 2, map_px / 2);
//      loadimage(&img_hide[i], BulletHide_FileName[i], map_px / 2, map_px / 2);
//    }
//  }
//}

bool Class_Bullet::ifMoveFinish() {
  Pos_XY endPos = { GetUnitPos().col * half_map_px, GetUnitPos().row * half_map_px };
  Pos_XY pos = GetXYPos();
  Pos_RC unit_pos = GetUnitPos();
  //终点坐标校正
  endPos = fix(endPos);
  //当前绘图坐标与移动终点的绘图坐标差大于每次刷新应移动的像素时，判定为未到达终点
  if (abs(pos.x - endPos.x) > GetSpeed() || abs(pos.y - endPos.y) > GetSpeed()) {
    return false;
  }
  else {
    SetXYPos(endPos);
    return true;
  }
}

//void Class_Bullet::checkHitWall(Class_Map& Map, UnitType TankType)
//{
//  if (!GetState())//子弹不存在直接返回
//  {
//    return;
//  }
//
//  Int mrow, mcol;//需要检查的地图坐标
//  MapInt* check1, * check2;//两个地图坐标上的取值（地形）
//  mrow = GetMapPos().row;
//  mcol = GetMapPos().col;
//  Direction direction = GetDirection();
//  bool ifHit = false;//假为没碰撞，真为碰撞，最后根据它的值判断是否让子弹消失
//  bool fix = false;//是否修正爆炸坐标
//  bool voice = TankType == CP ? false : true;//是否播放音效
//
//  //根据方向获取需要判断碰撞的地图点
//  check1 = Map.GetMap(mrow, mcol);
//  check2 = check1;//过编译器错误检查
//  switch (direction)
//  {
//  case UP:
//  case DOWN:
//    check2 = Map.GetMap(mrow, mcol + 1);
//    break;
//  case LEFT:
//  case RIGHT:
//    check2 = Map.GetMap(mrow + 1, mcol);
//    break;
//  default:
//    break;
//  }
//
//  //判断地形，处理碰撞结果
//
//  if (*check1 == BORDER || *check2 == BORDER)//击中边界，子弹直接消失
//  {
//    if (voice)
//    {
//      mciSendString(_T("play BoomBullet from 0"), 0, 0, 0);
//    }
//    changeState();
//    return;
//  }
//
//  //地形破坏检查
//  if (GetLev() == HEAVY)//玩家装甲最高时，一次消除一整块砖
//  {
//    fix = true;
//    switch (direction)
//    {
//    case UP:
//    case DOWN:
//      if (*check1 <= IRON)
//      {
//        if (*check1 & WALL_RIGHT || *check1 == IRON)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//      }
//      if (*check2 <= IRON)
//      {
//        if (*check2 & WALL_LEFT || *check2 == IRON)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//      }
//      break;
//    case LEFT:
//    case RIGHT:
//      if (*check1 <= IRON)
//      {
//        if (*check1 & WALL_DOWN || *check1 == IRON)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//      }
//      if (*check2 <= IRON)
//      {
//        if (*check2 & WALL_UP || *check2 == IRON)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//      }
//      break;
//    default:
//      break;
//    }
//    if (ifHit)
//    {
//      if (voice)
//      {
//        mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//      }
//    }
//  }
//  else//玩家普通情况下一次只消除半块砖，并且子弹会被铁块挡住
//  {
//    switch (direction)
//    {
//    case UP:
//      //处理第一层砖
//      if (*check1 <= WALL && *check1 & WALL_DR)
//      {
//        *check1 = *check1 & WALL_UP;
//        ifHit = true;
//      }
//      if (*check2 <= WALL && *check2 & WALL_DL)
//      {
//        *check2 = *check2 & WALL_UP;
//        ifHit = true;
//      }
//      if (ifHit)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//        }
//      }
//      //碰到钢铁
//      if (*check1 == IRON || *check2 == IRON)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomBullet from 0"), 0, 0, 0);
//        }
//        ifHit = true;
//      }
//      if (ifHit)//如果在第一层就发生了碰撞，子弹消失并返回
//      {
//        changeState();
//        return;
//      }
//      //判断第二层
//      else
//      {
//        if (*check1 <= WALL && *check1 & WALL_UR)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//        if (*check2 <= WALL && *check2 & WALL_UL)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//        if (ifHit)
//        {
//          fix = true;
//          if (voice)
//          {
//            mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//          }
//        }
//      }
//      break;
//    case LEFT:
//      //处理第一层砖
//      if (*check1 <= WALL && *check1 & WALL_DR)
//      {
//        *check1 = *check1 & WALL_LEFT;
//        ifHit = true;
//      }
//      if (*check2 <= WALL && *check2 & WALL_UR)
//      {
//        *check2 = *check2 & WALL_LEFT;
//        ifHit = true;
//      }
//      if (ifHit)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//        }
//      }
//      //碰到钢铁
//      if (*check1 == IRON || *check2 == IRON)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomBullet from 0"), 0, 0, 0);
//        }
//        ifHit = true;
//      }
//      if (ifHit)//如果在第一层就发生了碰撞，子弹消失并返回
//      {
//        changeState();
//        return;
//      }
//      //判断第二层
//      else//判断第二层
//      {
//        if (*check1 <= WALL && *check1 & WALL_DL)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//        if (*check2 <= WALL && *check2 & WALL_UL)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//        if (ifHit)
//        {
//          fix = true;
//          if (voice)
//          {
//            mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//          }
//        }
//      }
//      break;
//    case DOWN:
//      //处理第一层砖
//      if (*check1 <= WALL && *check1 & WALL_UR)
//      {
//        *check1 = *check1 & WALL_DOWN;
//        ifHit = true;
//      }
//      if (*check2 <= WALL && *check2 & WALL_UL)
//      {
//        *check2 = *check2 & WALL_DOWN;
//        ifHit = true;
//      }
//      if (ifHit)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//        }
//      }
//      //碰到钢铁
//      if (*check1 == IRON || *check2 == IRON)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomBullet from 0"), 0, 0, 0);
//        }
//        ifHit = true;
//      }
//      if (ifHit)//如果在第一层就发生了碰撞，子弹消失并返回
//      {
//        changeState();
//        return;
//      }
//      //判断第二层
//      else
//      {
//        if (*check1 <= WALL && *check1 & WALL_DR)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//        if (*check2 <= WALL && *check2 & WALL_DL)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//        if (ifHit)
//        {
//          fix = true;
//          if (voice)
//          {
//            mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//          }
//        }
//      }
//      break;
//    case RIGHT:
//      //处理第一层砖
//      if (*check1 <= WALL && *check1 & WALL_DL)
//      {
//        *check1 = *check1 & WALL_RIGHT;
//        ifHit = true;
//      }
//      if (*check2 <= WALL && *check2 & WALL_UL)
//      {
//        *check2 = *check2 & WALL_RIGHT;
//        ifHit = true;
//      }
//      if (ifHit)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//        }
//      }
//      //碰到钢铁
//      if (*check1 == IRON || *check2 == IRON)
//      {
//        if (voice)
//        {
//          mciSendString(_T("play BoomBullet from 0"), 0, 0, 0);
//        }
//        ifHit = true;
//      }
//      if (ifHit)//如果在第一层就发生了碰撞，子弹消失并返回
//      {
//        changeState();
//        return;
//      }
//      //判断第二层
//      else
//      {
//        if (*check1 <= WALL && *check1 & WALL_DR)
//        {
//          *check1 = EMPTY;
//          ifHit = true;
//        }
//        if (*check2 <= WALL && *check2 & WALL_UR)
//        {
//          *check2 = EMPTY;
//          ifHit = true;
//        }
//        if (ifHit)
//        {
//          fix = true;
//          if (voice)
//          {
//            mciSendString(_T("play BoomWall from 0"), 0, 0, 0);
//          }
//        }
//      }
//      break;
//    default:
//      break;
//    }
//  }
//
//  if (ifHit)
//  {
//    changeState(fix);
//  }
//}

Pos_XY Class_Bullet::fix(Pos_XY pos) {
  switch (GetDirection())//绘图坐标纠正
  {
    case UP:
    case DOWN:
      pos.x = pos.x + map_px - half_map_px / 2;
      break;
    case LEFT:
    case RIGHT:
      pos.y = pos.y + map_px - half_map_px / 2;
      break;
    default:
      break;
  }
  return pos;
}
