#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lessonScore.h"


void initLessonLink(lessonLink *l)//初始化头节点
{
    createLessonNode(l,0,0,0,"\0",0,"\0");
}

int createLessonNode(LessonScore **lnode,long lessonCode,short score,char time,char lessonName[],short credit,char teacher[])
{
    (*lnode)=(LessonScore*)malloc(sizeof(LessonScore));
    (*lnode)->next=NULL;
    (*lnode)->lessonCode=lessonCode;
    (*lnode)->socre=score;
    (*lnode)->time=time;
    (*lnode)->credit=credit;
    strcpy((*lnode)->lessonName,lessonName);
    strcpy((*lnode)->teacher,teacher);
    return 0;
}

int insertLessonNode(lessonLink l,LessonScore *lnode,int x)//在指定位置插入，成功返回0，失败返回1
{
    if (x<=0)
    {
        /* code */
        return 1;//错误位置
    }
    
    if ((!l)&&(!lnode))//若有指针空，返回1
        return 1;
    lessonLink p=l;
    for (int i = 0; i < x; i++)//定位到指定位置
    {
        /* code */
        if (!p->next)//长度不够
            return 1;
        p=p->next;
    }
    lnode->next=p->next;
    p->next=lnode->next;
    return 0;
}

int searchLesson(lessonLink h, long lessonNumber,LessonScore **conclusion)//根据课程编号在搜索h中搜索，返回最大的小于等于指针，1代表找到，0代表未找到，-1出错
{
    if (!h)
        return -1;
    LessonScore *p=h;
    int flag=0;
    while (p->next)
    {
        if (p->next->lessonCode==lessonNumber)
        {
            flag=1;
            p=p->next;
            break;
        }
        if (p->next->lessonCode>lessonNumber)
        {
            flag=0;
            break;
        }
        p=p->next;
    }
    *conclusion=p;
    return flag;
}

void lessonBackInsert(LessonScore *p,LessonScore *q)//将q插入p的后面
{
    q->next=p->next;
    p->next=q;
}

int lessonDelete(lessonLink h,long lessonCode)//删除节点，1代表成功，0代表出错
{
     if (!h)
        return -1;
    LessonScore *p=h;
    int flag=0;
    while (p->next)
    {
        if (p->next->lessonCode==lessonCode)
        {
            flag=1;
            LessonScore *q = p->next;
            free(p->next);
            p->next=q;
            break;
        }
        if (p->next->lessonCode>lessonCode)
        {
            flag=0;
            break;
        }
    }
    return flag;
}

void lessonChange(LessonScore *lnode,long lessonCode,short score,char time,char lessonName[],short credit,char teacher[])
{
    (*lnode).lessonCode=lessonCode;
    (*lnode).socre=score;
    (*lnode).time=time;
    (*lnode).credit=credit;
    if (lnode->lessonName!=lessonName)
        strcpy((*lnode).lessonName,lessonName);
    if (lnode->teacher!=teacher)
        strcpy((lnode)->teacher,teacher);
}

void lessonPrint(LessonScore *p)
{
    printf("%10ld",p->lessonCode);
    printf("%10s",p->lessonName);
    printf("%10s",p->teacher);
    printf("%10d",p->socre);
    printf("%10d",p->credit);
    printf("%10c",p->time);
    printf("\n");
}

int ltest()
{
    lessonLink h;
    LessonScore *p;
    initLessonLink(&h);
    createLessonNode(&(h->next),10,78,'1',"课程名",2,"张三");
    lessonPrint(h->next);
    int i=searchLesson(h,10,&p);
    lessonPrint(p);
    printf("%p\n",p);
    printf("%d\n",i);
    i=searchLesson(h,7,&p);
    lessonPrint(p);
    printf("%p\n",p);
    printf("%d\n",i);
    i=searchLesson(h,17,&p);
    lessonPrint(p);
    printf("%p\n",p);
    printf("%d\n",i);

    return 0;
}