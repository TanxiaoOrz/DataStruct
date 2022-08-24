#ifndef _lessonScore_H
#define _lessonScore_H

#include "Structure.h"



void initLessonLink(lessonLink *l); //初始化头节点
int createLessonNode(LessonScore **lnode,long lessonCode,short score,char time,char lessonName[],short credit,char teacher[]); //创建成绩节点
int insertLessonNode(lessonLink l,LessonScore *lnode,int x);//在指定位置插入，成功返回0，失败返回1
int searchLesson(lessonLink h, long lessonNumber,LessonScore **conclusion);//根据课程编号在搜索h中搜索，返回最大的小于等于指针，1代表找到，0代表未找到，-1出错
void lessonBackInsert(LessonScore *p,LessonScore *q);//将q插入p的后面
int lessonDelete(lessonLink h,long lessonCode);//删除节点，1代表成功，0代表出错
void lessonChange(LessonScore *lnode,long lessonCode,short score,char time,char lessonName[],short credit,char teacher[]);//修改课程成绩信息
void lessonPrint(LessonScore *p);//输出成绩信息
int newLesson(lessonLink h);//根据输入创建新的课程并插入课程链表中,1表示已存在
void lessonPrintHead(lessonLink h);//遍历输出课程链表
int changeLesson(lessonLink h);//根据输入修改课程信息，1代表输入的编号不存在
void deleteLesson(lessonLink h);//根据输入删除节点


#endif