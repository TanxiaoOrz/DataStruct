#include <stdlib.h>
#include <stdio.h>
#include "function.h"


int insertStuLinkPos(stuhead stuh,pSNode stu,int x)//在指定位置插入，成功返回0，失败返回1
{
    if (x<=0)
    {
        /* code */
        return 1;//错误位置
    }
    
    if (!stuh||!stuh->h)//若有指针空，返回1
        return 1;
    pSNode p=stuh->h;
    for (int i = 1; i < x; i++)//定位到指定位置
    {
        /* code */
        if (!p->next)//长度不够
            return 1;
        p=p->next;
    }
    stu->next=p->next;
    p->next=stu;
    stu->prev=p;
    if (stu->next)
        stu->next->prev=stu;
    return 0;
}

int rankcal(stuhead stuh,pSNode stu,int type) //输入要查询的序号和成绩类型，遍历链表统计排名并返回
{
    pSNode p=stuh->h->next;
    int rank=1;
    while (p)
    {
        switch (type)
        {
        case 0:{
            if (p->stu->score>stu->stu->score)
            {
                rank ++;
                break;
            }   
        }
        case 1:{
            if (p->stu->weightScore>stu->stu->weightScore)
            {
                rank ++;
                break;
            }  
        }    
        case 2:{
            if (p->stu->weightGrade>stu->stu->weightGrade)
            {
                rank ++;
                break;
            }  
        }
        }
        p=p->next;
    }
    return rank;
}

void printAllstuRank(stuhead stuh,int type) //安排序和选择类型输出学生信息
{
    char typeTitle[3][13]={"综测分数","加权成绩","加权绩点"};
    printf("%s排序如下\n  排名",typeTitle[type]);
    printTitleStudent();
    pSNode p=stuh->h->next;
    int i=1;
    while (p)
    {
        PStu stu =p->stu;
        printf("%8d",i);
        printf("%12ld",stu->studentNumber);
        printf("%12s",stu->studentName);
        printf("%12hd",stu->age);
        printf("%12c",stu->sex);
        printf("%12f",stu->weightScore);
        printf("%12f",stu->weightGrade);
        printf("%12hd",stu->credit);
        printf("%12d",stu->show);
        printf("\n");
        p=p->next;
    }
}

int showSingleStuRank(stuhead stuh) //对单个学生选择类型输出排名
{
    char typeTitle[3][13]={"综测分数","加权成绩","加权绩点"};
    int i=0;
    long code=0;
    printf("选择想要查询排名的学生学号______________\b\b\b\b");
    scanf("%ld",&code);
    KeyType key;
    key.stu=NULL;
    key.studentNumber=code;
    SearchResult result = SearchBTree(stuh->t, key);
    if (result.flag=='N')
    {
        /* code */
        printf("该学号不存在\n");
        return 0;
    }

    printf("请选择排序标准:0、综测分数\n");
    printf("               1、加权成绩\n");
    printf("               2、加权绩点\n");
    printf("请输入标准的序号_____\b\b\b");
    scanf("%d",&i);
    if (i<0||i>2)
        return 0;
    int rank =rankcal(stuh,result.p->key[result.position].stu,i);
    printTitleStudent();
    printstudent(result.p->key[result.position].stu->stu);
    printf("该学生%s的排名是%d\n",typeTitle[i],rank);
    return 1;
}

int rankStu(stuhead stuh) //重新排序学生并输出
{
    printf("请选择排序标准:0、综测分数\n");
    printf("               1、加权成绩\n");
    printf("               2、加权绩点\n");
    printf("请输入标准的序号_____\b\b\b");
    int i=0;
    scanf("%d",&i);
    if (i<0||i>2)
        return 1;
    pSNode wait = stuh->h->next;
    pSNode next = wait->next;
    stuh->h->next=NULL;
    while (wait)        //使用插入排序
    {
        /* code */
        next = wait->next;

        int p = rankcal(stuh,wait,p);
        insertStuLinkPos(stuh,wait,p);

        wait = next;
    }
    printAllstuRank(stuh,i);
    return 0;
}

int testF1()
{
    stuhead stuh;
    studentHeadInital(&stuh);
    readStudent(stuh);
    initalActRec();
    readActRec();
    printf("当前链表\n");
    PrintAllstudent(stuh->h);
    testF2(stuh);  
    PrintAllstudent(stuh->h);
    return 1;
}

