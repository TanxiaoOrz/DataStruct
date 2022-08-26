#ifndef _activity_H
#define _activity_H

#include "Structure.h"

extern ActivityRecord actRec; //全局活动记录线性表

void initalActRec(); //初始化全局活动记录线性表
Activity* createAct(char name[],short showScore,char time[],char tail[]); //新建活动
void initalActRec(); //初始化全局活动记录线性表
void addActRec(Activity *act); //增加记录
void printActTitle(); //输出活动标题
void printAct(Activity *acr,int i);   //输出序号和活动名
void printActRec(); //输出所有活动记录
short newActRec(); //根据输入新增记录
short deleteActRec(int i); //删除i记录，0失败,返回p的showScore
Activity* searchActRec(int i); //返回序号对应活动指针
int writeActRec();//存储活动表
int readActRec();    //读取活动表
int changeActRec(Activity *act,char name[],char time[],char tail[],short showScore); //返回综测分变化值

#endif