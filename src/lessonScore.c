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
            LessonScore *q = p->next->next;
            free(p->next);
            p->next=q;
            break;
        }
        if (p->next->lessonCode>lessonCode)
        {
            flag=0;
            break;
        }
        p=p->next;
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

void lessonPrintHead(lessonLink h)//遍历输出课程链表
{
    if (!h||h->next==NULL)//判断空链表
    {
        printf("无课程成绩信息");
    }   
    LessonScore *p;
    printf("  课程编号    课程名      教师      成绩      学分  修读学期\n");
    for ( p = h->next;p!=NULL;p=p->next)//遍历
    {
        lessonPrint(p);
    }
    
}

int newLesson(lessonLink h)//根据输入创建新的课程并插入课程链表中,1表示已存在
{
    long lessonCode;
    short score;
    char time;
    char lessonName[10];
    short credit;
    char teacher[10];
    printf("请输入课程编号__________________\b\b\b\b\b");
    scanf("%ld",&lessonCode);
    printf("请输入分数__________________\b\b\b\b\b");
    scanf("%hd",&score);
    printf("请输入修读学期数字__________________\b\b\b\b\b");
    scanf("%c",&time);
    scanf("%c",&time);
    printf("请输入课程名__________________\b\b\b\b\b");
    scanf("%s",lessonName);
    printf("请输入学分__________________\b\b\b\b\b");
    scanf("%hd",&credit);
    printf("请输入教师__________________\b\b\b\b\b");
    scanf("%s",teacher);
    LessonScore *p,*q;//p是插入位置，q是创建的节点指针
    int i=searchLesson(h,lessonCode,&p);
    if (i)
    {
        printf("该编号已存在");
        return 1;
    }
    else
    {
        createLessonNode(&q,lessonCode,score,time,lessonName,credit,teacher);
        lessonBackInsert(p,q);
        return 0;
    }
}

int changeLesson(lessonLink h)//根据输入修改课程信息，1代表输入的编号不存在
{
    long lessonCode;
    short score;
    char time;
    char lessonName[10];
    short credit;
    char teacher[10];
    printf("请输入要修改的课程编号__________________\b\b\b\b\b");
    scanf("%ld",&lessonCode);
    LessonScore *p;
    int i=searchLesson(h,lessonCode,&p);
    if (!i)
    {
        printf("该编号不存在");
        return 1;
    }
    printf("请输入新的分数__________________\b\b\b\b\b");
    scanf("%hd",&score);
    printf("请输入新的修读学期数字__________________\b\b\b\b\b");
    scanf("%c",&time);
    scanf("%c",&time);
    printf("请输入新的课程名__________________\b\b\b\b\b");
    scanf("%s",lessonName);
    printf("请输入新的学分__________________\b\b\b\b\b");
    scanf("%hd",&credit);
    printf("请输入新的教师__________________\b\b\b\b\b");
    scanf("%s",teacher);
    lessonChange(p,lessonCode,score,time,lessonName,credit,teacher);
    printf("修改成功,修改后的课程信息如下\n");
    printf("  课程编号    课程名      教师      成绩      学分  修读学期\n");
    lessonPrint(p);
    return 0;    
}

void deleteLesson(lessonLink h)//根据输入删除节点
{
    long lessonCode;
    printf("请输入要删除的课程编号__________________\b\b\b\b\b");
    scanf("%ld",&lessonCode);
    int i=lessonDelete(h,lessonCode);
    if (i)
    {
        printf("删除成功");
    }
    else
    {
        printf("该编号不存在");
    }
}

int ltest1()
{
    lessonLink h;
    initLessonLink(&h);
    for (size_t i = 0; i < 3; i++)
    {
        /* code */
        newLesson(h);
        lessonPrintHead(h);
    }
    deleteLesson(h);
    lessonPrintHead(h);
    return 0;
}

int ltest()
{
    lessonLink h;
    LessonScore *p,*q;
    initLessonLink(&h);
    createLessonNode(&p,10,78,'1',"课程名",2,"张三");
    int k=searchLesson(h,p->lessonCode,&q);
    if (!k)
    {
        lessonBackInsert(q,p);
    }
    lessonPrintHead(h);
    



/*

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
    printf("%d\n",i);*/

    return 0;
}