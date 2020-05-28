#include "Class_ComputerPlayer.h"
#include "Class_Timer.h"

Class_ComputerPlayer::Class_ComputerPlayer()
  :Class_Tank(CP_born_pos[(MaxEnemy - CP_count) % CP_born_pos_num], CP) {
  ReduceEnemy();//减少剩余坦克
  //AddLivingEnemy();//增加一个场上的坦克

  //随机设置坦克的装甲等级
  int num = rand() % ArmorCount;
  switch (num) {
    case NORMAL:
      SetArmorLev(NORMAL);
      break;
    case LIGHT:
      SetArmorLev(LIGHT);
      break;
    case STRONG:
      SetArmorLev(STRONG);
      break;
    case HEAVY:
      SetArmorLev(HEAVY);
      break;
    default:
      break;
  }

  //设置一下坦克行走的时间（随机值）
  run_time = rand() % MaxRunningTime + Class_Timer::GetGameTime();
}

Class_ComputerPlayer::Class_ComputerPlayer(Pos_RC map_pos)
  :Class_Tank(CP_born_pos[(MaxEnemy - CP_count) % CP_born_pos_num], CP) {}

Class_ComputerPlayer::~Class_ComputerPlayer() {
  //ReduceLivingEnemy();//减少一个场上的坦克
}

void Class_ComputerPlayer::CountToMax() {
  CP_count = MaxEnemy;
}

void Class_ComputerPlayer::ReduceEnemy() {
  CP_count--;
}

int Class_ComputerPlayer::GetEnemyCount() {
  return CP_count;
}

void Class_ComputerPlayer::renewRun(Class_Map &map) {
  DWORD cur_time = Class_Timer::GetGameTime();//获取当前游戏时间
  int newDirection = GetDirection();//新移动方向

  if (cur_time > run_time) {
    //如果当前时间超过了坦克移动的时间点
    //就改变当前坦克的移动状态（方向和持续时间）
    newDirection = rand() % DirectionCount;
    run_time = rand() % MaxRunningTime + Class_Timer::GetGameTime();
  }
  move((Direction)newDirection, map);
}

float Class_ComputerPlayer::GetSpeed() const {
  //以下代码可以放到电脑玩家中
  if (GetArmorLev() == LIGHT) {
    return FastSpeed / 1000.0f;
  }
  if (GetArmorLev() == HEAVY) {
    return SlowSpeed / 1000.0f;
  }
  return NormalSpeed / 1000.0f;
}

//void Class_ComputerPlayer::LivingCountToMin()
//{
//  CP_living_count = 0;
//}
//
//void Class_ComputerPlayer::ReduceLivingEnemy()
//{
//  CP_living_count--;
//}
//
//void Class_ComputerPlayer::AddLivingEnemy()
//{
//  CP_living_count++;
//}
//
//int Class_ComputerPlayer::GetLivingEnemyCount()
//{
//  return CP_living_count;
//}

//静态变量初始化
int Class_ComputerPlayer::CP_count = MaxEnemy;
//int Class_ComputerPlayer::CP_living_count = 0;
