#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"
#include "bTree.h"
#include "student.h"
#include "lessonScore.h"
#include "activity.h"
#include "function.h"


extern int test1();
extern int test2();
extern int ltest();
extern int ltest1();
extern void testS();
extern int testA();
extern int testF1();
extern int testF2();

void initalizeAndLoda(stuhead *stuh); //初始化学生头指针和活动表，创建树，从文件中读取
void userChoosePanel(stuhead stuh); //选用户界面
void studentPanel(stuhead stuh);//学生界面
void chargePanel(stuhead stuh);//班主任界面
void instructorPanel(stuhead stuh);//辅导员界面
void save(stuhead stuh); //保存所有信息
int check(stuhead stuh); //重新计算综测分和成绩信息，避免txt文档修改错误,1有，0无

int main()
{
    stuhead stuh;
    initalizeAndLoda(&stuh);
    int flag = check(stuh);
    if (flag)
    {
        //printf("!!!存储文件被错误修改，正在修正并重新保存!!!\n");
        save(stuh);
        //system("pause");
        system("cls");
    }
    userChoosePanel(stuh);
    save(stuh);
    system("pause");    // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}

int check(stuhead stuh)
{
    pSNode p=stuh->h->next;
    int flag=0;
    while (p)
    {
        /* code */
        float weightscore=p->stu->weightScore,weightgrade=p->stu->weightGrade;
        int show=p->stu->show;
        calStuAct(p->stu);
        calStuLess(p->stu);
        if ((weightscore-(p->stu->weightScore))||(weightgrade-(p->stu->weightGrade))||(show-(p->stu->show)))
        {
            /* code */
            flag=1;
        }
        p=p->next;
    }
    return flag;
}

void initalizeAndLoda(stuhead *stuh) //初始化学生头指针和活动表，创建树，从文件中读取
{
    studentHeadInital(stuh);
    readStudent(*stuh);
    initalActRec();
    readActRec();
}

void userChoosePanel(stuhead stuh) //选用户界面
{
    while (1)
    {
        printf("\t欢迎来到班级信息管理系统\n");
        printf("============================================\n");
        printf("  请选择登录用户:\n");
        printf("\t\t1) 学生 \n");
        printf("\t\t2)班主任\n");
        printf("\t\t3)辅导员\n");
        printf("\t\t0) 退出\n");
        printf("============================================\n");
        printf("    请输入选项序号_____\b\b\b");
        int i = 0;
        scanf("%d",&i);
        switch (i)
        {
            case 1:
            {    
                studentPanel(stuh);
                printf("\n\t");
                system("pause");
                system("cls");            
                break;
            }
            case 2:
            {       
                chargePanel(stuh);
                printf("\n\t");
                system("pause");
                system("cls");            
                break;
            }
            case 3:
            {       
                instructorPanel(stuh);
                printf("\n\t");
                system("pause");
                system("cls");            
                break;
            }
            case 0:
            {
                printf("   正在退出\n");
                return ;
            }
            default:
            {
                printf("！！！输入错误，自动保存并退出\n");
                return ;
            } 
        }
        system("cls");
    }
}

void save(stuhead stuh) //保存所有信息
{
    writeStudent(stuh);
    writeActRec();
    printf("   保存完成\n   ");
}

void studentPanel(stuhead stuh)//学生界面
{
    system("cls");
    while (1)
    {
        printf("\t欢迎学生来到班级信息管理系统\n");
        printf("================================================\n");
        printf("  请选择使用功能:\n");
        printf("\t\t1)新增学生基本信息\n");
        printf("\t\t2)修改学生基本和课程信息\n");
        printf("\t\t3)根据学号查询学生信息\n");
        printf("\t\t4)根据学号删除学生信息\n");
        printf("\t\t5)根据学号获取学生排名\n");
        printf("\t\t6)输出所有学生信息\n");
        printf("\t\t0)返回登录界面\n");
        printf("================================================\n");
        printf("    请输入选项序号_____\b\b\b");
        int i = 0;
        scanf("%d",&i);
        switch (i)
        {
            case 1:
            {    
                newStudent(stuh);
                system("cls");            
                break;
            }
            case 2:
            {       
                int l[3]={1,1,0};
                changeStu(stuh,l);
                system("cls");            
                break;
            }
            case 3:
            {       
                showSingleStudent(stuh);
                system("cls");            
                break;
            }
            case 4:
            {       
                deleteStudent(stuh);
                system("cls");            
                break;
            }
            case 5:
            {       
                showSingleStuRank(stuh);
                system("cls");            
                break;
            }
            case 6:
            {       
                PrintAllstudent(stuh->h);
                system("pause");
                system("cls");            
                break;
            }
            case 0:
            {
                printf("\t\t正在退出");
                return ;
            }

            default:
            {
                printf("！！！输入错误，自动退回登录界面");
                return ;
            } 
        }
    }
}

void instructorPanel(stuhead stuh)//辅导员界面
{
    system("cls");
    while (1)
    {
        printf("\t欢迎辅导员来到班级信息管理系统\n");
        printf("=================================================\n");
        printf("  请选择使用功能:\n");
        printf("\t\t1)根据学号查询学生信息\n");
        printf("\t\t2)新增或修改或删除学生课程信息\n");
        printf("\t\t3)按成绩排序输出学生信息和排名\n");
        printf("\t\t4)按绩点排序输出学生信息和排名\n");
        printf("\t\t5)输出所有学生信息\n");
        printf("\t\t0)返回登录界面\n");
        printf("================================================\n");
        printf("    请输入选项序号_____\b\b\b");
        int i = 0;
        scanf("%d",&i);
        switch (i)
        {
            case 1:
            {    
                showSingleStudent(stuh);
                system("cls");            
                break;
            }
            case 2:
            {       
                int l[3]={0,1,0};
                changeStu(stuh,l);
                system("cls");            
                break;
            }
            case 3:
            {       
                rankStu(stuh,1);
                system("cls");            
                break;
            }
            case 4:
            {       
                rankStu(stuh,2);
                system("cls");            
                break;
            }
            case 5:
            {       
                PrintAllstudent(stuh->h);
                system("pause");
                system("cls");            
                break;
            }
            case 0:
            {
                printf("\t\t正在退出");
                return ;
            }
            
            default:
            {
                printf("！！！输入错误，自动退回登录界面");
                return ;
            } 
        }
    }
}

void chargePanel(stuhead stuh)//班主任界面
{
    system("cls");
    while (1)
    {
        printf("\t欢迎班主任来到班级信息管理系统\n");
        printf("==================================================\n");
        printf("  请选择使用功能:\n");
        printf("\t\t1)新建班级活动信息\n");
        printf("\t\t2)修改班级活动信息\n");
        printf("\t\t3)删除班级活动信息\n");
        printf("\t\t4)查询活动出勤信息\n");
        printf("\t\t5)根据学号修改学生出勤\n");
        printf("\t\t6)根据学号查询学生信息\n");
        printf("\t\t7)输出所有学生信息\n");
        printf("\t\t8)对学生信息按综测分排序\n");
        printf("\t\t0)返回登录界面\n");
        printf("================================================\n");
        printf("    请输入选项序号_____\b\b\b");
        int i = 0;
        scanf("%d",&i);
        switch (i)
        {
            case 1:
            {    
                newActStu(stuh);
                system("cls");            
                break;
            }
            case 2:
            {       
                changeActStu(stuh);
                system("cls");            
                break;
            }
            case 3:
            {       
                deleteActStu(stuh);
                system("cls");            
                break;
            }
            case 4:
            {       
                showActPre(stuh);
                system("cls");            
                break;
            }
            case 5:
            {       
                int l[3]={0,0,1};
                changeStu(stuh,l);
                system("cls");            
                break;
            }
            case 6:
            {       
                showSingleStudent(stuh);
                system("cls");            
                break;
            }
            case 7:
            {       
                PrintAllstudent(stuh->h);
                system("pause");
                system("cls");            
                break;
            }
            case 8:
            {       
                rankStu(stuh,0);
                system("cls");            
                break;
            }
            case 0:
            {
                printf("\t\t正在退出");
                return ;
            }
            
            default:
            {
                printf("！！！输入错误，自动退回登录界面");
                return ;
            } 
        }
    }
}