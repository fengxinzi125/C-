/*********************************************************************************************************
* 模块名称: main.c
* 摘    要: C语言大作业
* 当前版本: 1.0.0
* 作    者: 风信子
* 完成日期: 2025年07月26日
* 内    容:
* 注    意:
**********************************************************************************************************
* 取代版本:
* 作    者:
* 完成日期:
* 修改内容:
* 修改文件:
*********************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>    
//引入多媒体库
#pragma comment(lib, "winmm.lib")
//引入自定义头文件
#include "DataType.h"
#include "Gettime.h"
#include "Display.h"
#include "Alarm.h"
//定义全局变量
Alarm g_alarm;
static int alarm_active = 0; //全局变量，表示闹钟是否激活

//中断回调函数，每隔500ms调用一次
void CALLBACK TimerCallback(UINT uTimerID, UINT uMsg, 
  DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2) 
{
  struct tm my_time;
  my_time = *Gettime();
  system("cls");
  DisPlay(my_time.tm_hour, my_time.tm_min, my_time.tm_sec);
  if (alarm_active > 0)
  {
    alarm_active--;
    printf("\n***********************\n");
    printf("!!!!!!!!Alarm!!!!!!!!!!!!");
    printf("\n***********************\n");
  }
  else if (g_alarm.is_available == 1 && alarm_active == 0)
  {
    printf("Alarm Time:%d-%d\n", g_alarm.hour, g_alarm.min);
  }

  if (CheckAlarm(&g_alarm, my_time.tm_hour, my_time.tm_min) == 1)
  {
    //响铃，激活闹钟，持续6次500ms
    alarm_active = 6;
    g_alarm.is_available = 0;
  }

  else
  {
    printf("No Alarm");
  }
  //操作提示
  printf("----------------------------------------\n");
  printf("1. input hour minute setAlarm (li: 07 30)\n");
  printf("2. input -1 -1 exit program\n");
  printf("please input: \n");
}

int main() 
{
  //读取文件中的闹钟设置，如果没有文件则初始化闹钟
   LoadAlarm(&g_alarm, "Alarm.txt");
   timeBeginPeriod(1);
   //设置定时器，每隔500ms调用一次TimerCallback函数
   MMRESULT timerID = timeSetEvent(500, 1, TimerCallback, 0, TIME_PERIODIC);
   //检查定时器是否设置成功
   if (timerID == 0)
   {
     printf("Alarm False");
   }

   int inputHour, inputMin;
   while (1)
   {
     if (scanf("%d %d", &inputHour, &inputMin) == 2)  //输入格式为数字，空格，数字
     {
       //推出机制
       if (inputHour == -1 && inputMin == -1)
       {
         break;
       }
       //设置闹钟时间
       SetTime(&g_alarm, inputHour, inputMin);
       //保存闹钟设置到文件中
       SaveAlarm(&g_alarm, "alarm.txt");
     }
   }
   //销毁定时器，释放资源
  timeKillEvent(timerID);
  //设置系统定时器分辨率为默认值
   timeEndPeriod(1);
  system("pause");
  return 0;
}