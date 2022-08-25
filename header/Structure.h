#ifndef _Structure_H
#define _Structure_H


typedef struct lessonScore
{
    unsigned long lessonCode; //课程编号
    short socre; //学生成绩
    char time; //修读学期
    char lessonName[20]; //课程名
    short credit; //学分
    char teacher[10];//任课教师    
    struct lessonScore *next;
}LessonScore,*lessonLink;

typedef struct activity
{
    char name[19];//名字
    short showScore;//综测分
    char time[11];//时间
    char tail[30];//备注
}Activity;

typedef struct activityRecord //线性表存储活动名
{
    Activity *act[50];
    unsigned short count;
}ActivityRecord;
//通过线性表存储活动名，活动的创建由班主任直接输入活动名，学生通过一个同样数量的字符数字表示相同下标的活动是否有参加


typedef struct student  //存储学生信息的单链表节点
{
    char studentName[10]; //姓名
    long studentNumber; //学号
    short age;//年龄
    char sex;//性别
    LessonScore *score;//单链表存储学习过的课程和成绩
    short socreFlag;//成绩是否修改过，如为1则下面三个成绩信息须重新计算
    float weightScore;//加权成绩
    float weightGrade;//加权绩点   
    short credit;//总学分
    char engageActivity[50];//活动参与情况
    int show;//综测分
    char showFlag;//活动变化变量
}Student, *PStu;

typedef struct doubleLinkStruct //双向链表节点
{
    /* data */
    PStu stu;
    struct doubleLinkStruct *prev;
    struct doubleLinkStruct *next;
}StuNode, *pSNode;



#endif