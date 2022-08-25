#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Structure.h"
#include "activity.h"

ActivityRecord actRec; //全局活动记录线性表

Activity* createAct(char name[],short showScore,char time[],char tail[]) //新建活动
{
    Activity *act =(Activity*)malloc(sizeof(Activity));
    strncpy(act->name,name,19);
    strncpy(act->time,time,11);
    strncpy(act->tail,tail,30);
    act->showScore=showScore;
    return act;
}

void initalActRec() //初始化全局活动记录线性表
{
    for (int i=0;i<50;i++)
    {
        actRec.act[i]=NULL;
    }
    actRec.count=0;
}

void addActRec(Activity *act) //增加记录
{
    actRec.act[actRec.count]=act;
    actRec.count++;
}

Activity* searchActRec(int i) //返回序号对应活动指针
{
    if (i<actRec.count&&i>=0)
    {
        return actRec.act[i];
    }
    else
    {
        return NULL;
    }
    
    
}

void printActTitle() //输出活动标题
{
    printf("序号        活动名称    综测分  活动时间        备注\n");
}

void printAct(Activity *acr,int i)   //输出序号和活动名
{
    printf("%2d",i);
    printf("%18s",acr->name);
    printf("%10hd",acr->showScore);
    printf("%10s",acr->time);
    printf("        %s",acr->tail);
    printf("\n");
}

void printActRec() //输出所有活动记录
{
    printActTitle();
    if (actRec.count)
    {
        for (size_t i = 0; i < actRec.count; i++)
        {
        printAct(actRec.act[i],i);
        }  
    }
    else 
    {
        printf("表内没有活动记录\n");
    }
    
    
     
}

void newActRec() //根据输入新增记录
{
    char name[19];//名字
    short showScore;//综测分
    char time[11];//时间
    char tail[30];//备注
    printf("请输入活动名称____________\b\b\b\b\b\b\b\b");
    scanf("%s",name);
    printf("请输入活动分数____________\b\b\b\b\b\b\b\b");
    scanf("%hd",&showScore);
    printf("请输入活动时间____________\b\b\b\b\b\b\b\b");
    scanf("%s",time);
    printf("请输入活动备注____________\b\b\b\b\b\b\b\b");
    scanf("%s",tail);
    addActRec(createAct(name,showScore,time,tail));
}

int deleteActRec(int i) //删除i记录，0失败,返回p的showScore
{
    Activity* p =searchActRec(i);
    if (p)
    {
        free(p);
        for (size_t j = i; i < (actRec.count-1); j++)
        {
            /* code */
            actRec.act[i]=actRec.act[i+1];
        }
        actRec.count--;
        return -(p->showScore);
    }
    else
    {
        return 0;
    }
}

int changeActRec(Activity *act,char name[],char time[],char tail[],short showScore) //返回综测分变化值
{
    int distance = act->showScore-showScore;
    act->showScore=showScore;
    strncpy(act->name,name,19);
    strncpy(act->time,time,11);
    strncpy(act->tail,tail,30);
    return distance;
}

int writeActRec() //存储活动表
{
    int flag;
    FILE *fp = fopen("Activity.txt","w");
    for (size_t i = 0;1; i++)
    {
        /* code */
        flag=fprintf(fp,"%s ",actRec.act[i]->name);
        flag=fprintf(fp,"%hd ",actRec.act[i]->showScore);
        flag=fprintf(fp,"%s ",actRec.act[i]->time);
        flag=fprintf(fp,"%s",actRec.act[i]->tail);
        if (i==actRec.count-1)
        {
            break;
        }
        else
        {
            fprintf(fp,"\n");
        } 
    }
    fclose(fp);
    return flag;
}

int readActRec()    //读取活动表
{
    int flag;
    FILE *fp = fopen("Activity.txt","r");
    int i=0;
    while (!feof(fp))
    {
        /* code */
        char name[19];//名字
        short showScore;//综测分
        char time[11];//时间
        char tail[30];//备注
        flag=fscanf(fp,"%s",name);
        flag=fscanf(fp,"%hd",&showScore);
        flag=fscanf(fp,"%s",time);
        flag=fscanf(fp,"%s",tail);
        actRec.act[i] = createAct(name,showScore,time,tail);
        i++;
        fgetc(fp);
    }
    actRec.count=i;
    fclose(fp);
    return flag;
}

int testA(){
    initalActRec();
    readActRec();    //读取活动表
    printActRec();
    for (size_t i = 0; i < 2; i++)
    {
        newActRec();
        printActRec();

    }
    writeActRec();
    return 0;
    for (size_t i = 0; i < 3; i++)
    {
        int k;
        printf("输入要修改的活动序号____________\b\b\b\b\b\b\b\b");
        scanf("%d",&k);
        Activity *act =searchActRec(k);
        if (act)
        {
            char name[19];//名字
            short showScore;//综测分
            char time[11];//时间
            char tail[30];//备注
            printf("请输入活动名称____________\b\b\b\b\b\b\b\b");
            scanf("%s",name);
            printf("请输入活动分数____________\b\b\b\b\b\b\b\b");
            scanf("%hd",&showScore);
            printf("请输入活动时间____________\b\b\b\b\b\b\b\b");
            scanf("%s",time);
            printf("请输入活动备注____________\b\b\b\b\b\b\b\b");
            scanf("%s",tail);
            changeActRec(act,name,time,tail,showScore);
            printActRec();
        }
        else
        {
            printf("没有该序号记录");
        }    
    }
    return 1;
    free(createAct("\0",2,"\0","\0"));
    return 0;
}

int testAold(){
    initalActRec();
    readActRec();    //读取活动表
    printActRec();
    for (size_t i = 0; i < 5; i++)
    {
        newActRec();
        printActRec();
    }
    for (size_t i = 0; i < 3; i++)
    {
        int k;
        scanf("%d",&k);
        if (deleteActRec(k))
        {
            printActRec();
        }
        else
        {
            printf("没有该序号记录");
        }    
    }
    return 1;
    free(createAct("\0",2,"\0","\0"));
    return 0;
}