#pragma once
#ifndef ALARM_H
#define ALARM_H

//定义闹钟结构体
typedef struct 
{
  int hour;
  int min;
  int is_available;
} Alarm;

void IninAlarm(Alarm* alarm); 
void SetTime(Alarm* alarm, int h, int m);
int CheckAlarm(Alarm* alarm, int Current_Hour, int Current_Min);
void SaveAlarm(Alarm* alarm, const char* filename);
void LoadAlarm(Alarm* alarm, const char* filename);

#endif // !ALARM_H

