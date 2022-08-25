#ifndef _student_H
#define _student_H

#include "bTree.h"

typedef struct studentHead//学生存储结构，存有头结点和树的根指针
{
    /* data */
    BTree t;
    pSNode h;
}StudentHead, *stuhead;




void studentCreate(Student **s,char name[],long code,short age,char sex);//创建学生结构
void printstudent(PStu stu);//输出单个学生信息
pSNode createStuNode(PStu stu);//创建学生节点，指向stu
void PrintAllstudent(pSNode head);//输出所有学生信息
void InsertStuLink(pSNode head,pSNode news);//头插法插入节点
void deleteStuLink(pSNode del);//在链表中删除该节点
void newStudent(stuhead stuh); //新建学生信息
void deleteStudent(stuhead stuh); //删除学生信息
void printTitleStudent(); //输出学生格式
void studentHeadInital(stuhead *stuh); //初始化学生存储管理结构

#endif