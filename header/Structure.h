#ifndef _Structure_H
#define _Structure_H

typedef struct lesson
{
    unsigned long lessonCode; //课程编号
    char lessonName[10]; //课程名
    short credit; //学分
    struct lesson *next;  
}Lesson;

typedef struct lessonScore
{
    unsigned long lessonCode; //课程编号
    short socre; //学生成绩
    char time; //修读学期
    struct lessonScore *next;
}LessonScore;

typedef struct activity //线性表存储活动名
{
    char activityName[10][50];
    unsigned short count;
}Activity;



typedef struct student
{
    char studentName[10]; //
    long studentNumber; //
    char controlFlag;/* 第一位置一代表该学生数据被修改过
                        第二位置一表示该学生平均成绩须重新统计
                        第三位置一表示该学生活动情形须重新统计
                        第四位置一表示修读学分需重新统计
                        第五位置代表性别
                        第六到七位置代表年龄于平均差异-1~2 */
    LessonScore *score;//单链表存储学习过的课程和成绩
    float weightScore;//加权成绩
    float weightGrade;//加权绩点
    char engageActivity[50];//活动参与情况
    short credit;//总学分
}Student;

#endif