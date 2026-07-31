//#include <stdio.h>
//#include <stdlib.h>
//
//struct Litchi {
//  char PingZhong[20];
//  char Color[20];
//  char ChanDi[20];
//  int Month;
//};
//
//int main() {
//  // 试图定义一个变量并初始化
//  struct Litchi Li = { "桂圆", "黄色", "广东", 2 };
//
//  // 试图用指针指向它
//  struct Litchi* p = &Li;    //Litchi* p是一个结构体指针，指向结构体变量Li的地址
//
//  printf("荔枝品种是%s\n", Li.PingZhong);
//  printf("荔枝品种是%s\n", p->PingZhong);
//  printf("荔枝品种是%p\n", &p+1);
//  return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct Litchi {
  char PingZhong[20];
  char Color[20];
  char ChanDi[20];
  int Month;
};

// 错误的修改方式：传值
//void UpdateStatus_Wrong(struct Litchi temp) {
//  temp.Month = 6;
//  strcpy(temp.Color, "红色");
//}

// 正确的修改方式：传址（传指针）
void UpdateStatus_Correct(struct Litchi* ptr) {
  // 【任务2：请在这里补全核心代码，使用 ptr 把月份改成 6，颜色改成 "红色"】
  ptr->Month = 6;
  strcpy(ptr->Color, "红色");
}

int main() {
  struct Litchi Li = { "桂味", "黄色", "广东", 2 };

  // 调用正确的函数来修改它
  UpdateStatus_Correct(&Li);
  printf("荔枝品种是%s\n", Li.PingZhong);
  printf("荔枝颜色是%s\n", Li.Color);
  printf("荔枝产地是%s\n", Li.ChanDi);
  printf("荔枝月份是%d\n", Li.Month);
  return 0;
}