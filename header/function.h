#ifndef _function_H
#define _function_H

#include "student.h"
#include "lessonScore.h"
#include "activity.h"

int rankcal(stuhead stuh, pSNode stu,int type); //输入要查询的序号和成绩类型，遍历链表统计排名并返回
int insertStuLinkPos(stuhead stuh,pSNode stu,int x);    //在指定位置插入，成功返回0，失败返回1
void printAllstuRank(stuhead h,int type); //安排序和选择类型输出学生信息
int showSingleStuRank(stuhead stuh); //对单个学生选择类型输出排名
int rankStu(stuhead stuh,int i); //重新排序学生并输出0综测，1成绩，2绩点

#endif