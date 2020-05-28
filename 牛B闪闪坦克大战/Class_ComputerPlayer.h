#pragma once
#include "Class_Tank.h"

const int CP_born_pos_num = 3;
const Pos_RC CP_born_pos[CP_born_pos_num] = { {2,2},{2,14},{2,26} };//敌人坦克出生坐标点
const int MaxEnemy = 20;//每一关的敌人总数
const int MaxLivingEnemy = 4;//场上存活的最大敌人数量
const int MaxRunningTime = 500;//坦克朝某方向运动的最长时间（毫秒）

class Class_ComputerPlayer :
  public Class_Tank {
public:
  Class_ComputerPlayer();
  Class_ComputerPlayer(Pos_RC map_pos);
  ~Class_ComputerPlayer();

  /*********************
  管理剩余敌人数目的函数
  *********************/
  //把敌人数量重置为最大（切换关卡的时候调用一次）
  static void CountToMax();
  //减少一个敌人
  static void ReduceEnemy();
  //获取当前敌人剩余数
  static int GetEnemyCount();


  //控制坦克自动奔跑
  void renewRun(Class_Map &map);

  /**********
  Get系列函数
  **********/
  //获取移动速度
  virtual float GetSpeed()const;

  /*************************
  管理场上存活敌人数目的函数
  *************************/
  ////把存活敌人数量重置为最小（切换关卡的时候调用一次）
  //static void LivingCountToMin();
  ////减少场上敌人数目
  //static void ReduceLivingEnemy();
  ////增加场上敌人数目
  //static void AddLivingEnemy();
  ////获取当前场上敌人数目
  //static int GetLivingEnemyCount();

  static int CP_count;//保存剩余、未出场的敌人总数
  //static int CP_living_count;//场上存活的敌人数量
  //笔记20200119：使用临时对象插入容器时，会调用一次构造函数和析构函数，容器存入对象时却不会调用构造函数，导致CP_living_count统计出错。

private:
  DWORD run_time;//保存运动结束时的时间点（单位：毫秒）
};
