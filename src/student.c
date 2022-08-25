#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "lessonScore.h"
#include "activity.h"


void studentCreate(Student **s,char name[],long code,short age,char sex)
{
    (*s)=(Student*)malloc(sizeof(Student));
    (*s)->studentNumber=code;
    (*s)->age=age;
    (*s)->sex=sex;
    strncpy((*s)->studentName,name,10);
    (*s)->socreFlag=0;
    (*s)->weightGrade=0;
    (*s)->weightScore=0;
    (*s)->credit=0;
    (*s)->show=0;
    (*s)->showFlag=0;
    initLessonLink(&((*s)->score));
    for (size_t i = 0; i < 50; i++)
    {
        /* code */
        (*s)->engageActivity[i]='N';
    }   
}

pSNode createStuNode(PStu stu){
	pSNode newNode = (pSNode)malloc(sizeof(StuNode));
	newNode->stu = stu;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
} 

void InsertStuLink(pSNode head,pSNode news){
	if(head->next==NULL)//空链表
    {
		news->next=head->next;
        head->next = news;
        news->prev =head;
		return ;
	} 

	news->next=head->next;
    head->next->prev=news;
    head->next = news;
    news->prev =head;
} 

void PrintAllstudent(pSNode head)
{
    if (head->next==NULL)
    {
        printf("该链表内没有学生");
        return ;
    }
    pSNode p = head->next;
    printTitleStudent(); //输出学生格式
    while(p!=NULL){
    	printstudent(p->stu);   //逐条输出学生
    	p=p->next;
	}
	printf("\n");
    return ;
} 

//删除指定元素
void deleteStuLink(pSNode del)
{
	pSNode p,n;
	p=del->prev;
    n=del->next;
    p->next=n;
    if (n!=NULL)
        n->prev=p;
    free(del->stu);
    free(del);
} 

void printTitleStudent() //输出学生格式
{
    printf("        学号        姓名        年龄        性别    加权成绩    加权绩点      总学分      综测分\n");
}

void printstudent(PStu stu)//格式化一行输出除活动参与情况和课程学习情况
{
    printf("%12ld",stu->studentNumber);
    printf("%12s",stu->studentName);
    printf("%12hd",stu->age);
    printf("%12c",stu->sex);
    printf("%12f",stu->weightScore);
    printf("%12f",stu->weightGrade);
    printf("%12hd",stu->credit);
    printf("%12d",stu->show);
    printf("\n");
}

void studentHeadInital(stuhead *stuh) //初始化学生存储管理结构
{
    *stuh = (stuhead) malloc(sizeof(StudentHead));
    InitBTree(&((*stuh)->t));
    (*stuh)->h=createStuNode(NULL);
}

void newStudent(stuhead stuh) //新建学生信息
{
    char name[10];
    long code;
    short age;
    char sex;
    KeyType key;
    PStu pstu=NULL;
    printf("请输入学生学号____________\b\b\b\b\b\b\b\b");
    scanf("%ld",&code);
    key.stu=NULL;
    key.studentNumber=code;
    SearchResult result = SearchBTree(stuh->t, key);
    if (result.flag=='Y')
    {
        /* code */
        printf("该学号已存在\n");
    }
    else
    {
        printf("请输入学生姓名____________\b\b\b\b\b\b\b\b");
        scanf("%s",name);
        printf("请输入学生性别____________\b\b\b\b\b\b\b\b");
        scanf("%c",&sex);
        scanf("%c",&sex);
        printf("请输入学生年龄____________\b\b\b\b\b\b\b\b");
        scanf("%hd",&age);
        studentCreate(&pstu,name,code,age,sex);
        pSNode pSnode = createStuNode(pstu);
        InsertStuLink(stuh->h,pSnode);//加入链表
        key.stu=pSnode;
        InsertBTree(&(stuh->t),result.position,key,result.p);//加入二叉树
    }    
}

void deleteStudent(stuhead stuh) //删除学生信息
{
    long code;
    KeyType key;
    printf("请输入要删除的学生学号____________\b\b\b\b\b\b\b\b");
    scanf("%ld",&code);
    key.stu=NULL;
    key.studentNumber=code;
    SearchResult result = SearchBTree(stuh->t, key);
    if (result.flag=='N')
    {
        /* code */
        printf("该学号不存在\n");
    }
    else
    {
        pSNode pSnode = result.p->key[result.position].stu;//获取链表节点
        deleteStuLink(pSnode);//链表中删除该节点
        BTreeDelete(&(stuh->t),key);//二叉树中删除索引
    }    
}

void showStuLesson(PStu stu) //显示学生的课程信息
{
    printTitleStudent();//打印学生头
    printstudent(stu);//显示该学生信息
    lessonPrintHead(stu->score);
}

void changePanelLesson( ) //修改学生的课程信息的显示面板
{
    printf("请选择信息修改方式\n");
    printf("\t1、新增课程信息\n");
    printf("\t2、修改课程信息\n");
    printf("\t3、删除课程信息\n");
    printf("\t4、返回上一界面\n");
    printf("输入数字选择选项_______\b\b\b\b");
}

void ChangeStuLesson(PStu stu) //修改学生的课程信息
{
    showStuLesson(stu);
    //lessonPrintHead(stu->score);
    changePanelLesson();
    int choose=0;
    while (1)
    {
        scanf("%d",&choose);
        switch (choose)
        {
            case 1:
            {
                newLesson(stu->score);
                //showStuLesson(stu);
                //system("pause");//临时暂停，查看信息
                return;
            }
            case 2:
            {
                changeLesson(stu->score);
                //showStuLesson(stu);
                //system("pause");//临时暂停，查看信息
                return;
            }
            case 3:
            {
                deleteLesson(stu->score);
                //showStuLesson(stu);
                //system("pause");//临时暂停，查看信息
                return;
            }
            case 4:
            {
                return ;
            }
            default:
            {
                 printf("输入错误，重新输入_______\b\b\b\b\n");
            }            
        }
    }
}

void changeStuBasic(PStu stu) //修改学生基本信息
{
    printf("当前信息为：\n");
    printTitleStudent();
    printstudent(stu);
    printf("请输入新的姓名____________\b\b\b\b\b\b\b\b");
    scanf("%s",stu->studentName);
    printf("请新的学生性别____________\b\b\b\b\b\b\b\b");
    scanf("%c",&stu->sex);
    scanf("%c",&stu->sex);
    printf("请新的学生年龄____________\b\b\b\b\b\b\b\b");
    scanf("%hd",&stu->age);
    printf("修改后信息为：\n");
    printTitleStudent();
    printstudent(stu);
    system("pause");
}

void printStuAct(PStu stu)  //输出学生出勤信息
{
    printTitleStudent();//打印学生头
    printstudent(stu);//显示该学生信息
    printf("\t\t出勤情况为Y代表出勤，N代表缺席\n");
    printf("出勤  ");
    printActTitle();
    for (size_t i = 0; i < actRec.count; i++)
    {
        /* code */
        printf("%4c   ",stu->engageActivity[i]);
        printAct(actRec.act[i],i);
    } 
}

void ChangeStuActivity(PStu stu) //修改学生的出勤信息
{
    printStuAct(stu);
    printf("如果原出勤信息是“Y”则改为“N”，反之改为“Y”");
    printf("请输入要修改出勤的活动序号____________\b\b\b\b\b\b\b\b");
    int i;
    scanf("%d",&i);
    if (searchActRec(i))    //如果序号合法
    {
        if (/* condition */stu->engageActivity[i]=='Y')
        {
            /* code */stu->engageActivity[i]='N';
        }else
        {
            stu->engageActivity[i]='Y';
        }   
    }else{
        printf("错误的序号\n");
    }
}

void calStuAct(PStu stu)    //计算综测分
{
    short show=0;
    for (size_t i = 0; i < actRec.count; i++)
    {
        /* code */
        if (stu->engageActivity[i]=='Y')
            show=show+actRec.act[i]->showScore;
    }
    stu->show=show;
}

int changeStu(stuhead stuh,int flag[]) //传入权限数组,返回值0代表未修改信息不用重置
{
    long code;
    KeyType key;
    printf("请输入要修改的学生学号____________\b\b\b\b\b\b\b\b");
    scanf("%ld",&code);
    key.stu=NULL;
    key.studentNumber=code;
    SearchResult result = SearchBTree(stuh->t, key);
    if (result.flag=='N')
    {
        /* code */
        printf("该学号不存在\n");
        return 0;

    }

    printf("请选择修改操作：\n");
    if (flag[0])
        printf("\t1、修改学生基本信息\n");
    if (flag[1])
        printf("\t2、修改课程成绩信息\n");
    if (flag[2])
        printf("\t3、修改活动出勤信息\n");
    printf("\t4、退出\n");
    printf("输入数字选择选项_______\b\b\b\b");

    int choose=0;
    while (1)
    {
        scanf("%d",&choose);
        switch (choose)
        {
            case 1:
            {
                if (flag[0])
                {
                    changeStuBasic(result.p->key[result.position].stu->stu);
                    //system("pause");//临时暂停，查看信息
                    return 1;
                }
                else
                {
                    printf("您无权执行该操作");
                    return 0;
                }
                
            }
            case 2:
            {
                if (flag[1])
                {
                    ChangeStuLesson(result.p->key[result.position].stu->stu);
                    calStuLess(result.p->key[result.position].stu->stu);
                    showStuLesson(result.p->key[result.position].stu->stu);
                    system("pause");//临时暂停，查看信息
                    return 1;
                }
                else
                {
                    printf("您无权执行该操作");
                    return 0;
                }
            }
            case 3:
            {
                if (flag[2])
                {
                    ChangeStuActivity(result.p->key[result.position].stu->stu);
                    calStuAct(result.p->key[result.position].stu->stu);
                    system("pause");//临时暂停，查看信息
                    return 1;
                }
                else
                {
                    printf("您无权执行该操作");
                    return 0;
                }
            }
            case 4:
            {
                return 0;
            }
            default:
            {
                 printf("输入错误，重新输入_______\b\b\b\b\n");
            }            
        }
    }
}

void calStuLess(PStu stu) //计算与成绩链表有关的变量
{
    float scoreAll=0,gradeAll=0;
    int credit=0; //初始化记录

    for (LessonScore *p = stu->score->next; p; p=p->next) //循环遍历
    {
        /* code */
        scoreAll=scoreAll+p->socre*p->credit;
        if (p->socre>=95)   //判断绩点
        {
            gradeAll=gradeAll+4.5*p->credit;;
        }
        else{
            if (p->socre>=90)
            {
                gradeAll=gradeAll+4*p->credit;;
            }
            else{
                if (p->socre>=85)
                {
                    gradeAll=gradeAll+3.5*p->credit;;
                }
                else{
                    if (p->socre>=80)
                    {
                        gradeAll=gradeAll+3*p->credit;;
                    }
                    else{
                        if (p->socre>=75)
                        {
                            gradeAll=gradeAll+2.5*p->credit;;
                        }
                        else{
                            if (p->socre>=70)
                            {
                                gradeAll=gradeAll+2*p->credit;;
                            }
                            else{
                                if (p->socre>=65)
                                {
                                    gradeAll=gradeAll+1.5;
                                }else{
                                    if (p->socre>=65)
                                    {
                                        gradeAll=gradeAll+1.5*p->credit;;
                                    }
                                    else{
                                        if (p->socre>=60)
                                        {
                                            gradeAll=gradeAll+1*p->credit;;
                                        }
                                        else
                                        {
                                            gradeAll=gradeAll;
                                        }
                                    }
                                }
                            } 
                        }
                    }
                }
            }
        }  
        credit=credit+p->credit;
    }
    if (credit)//如果不是空表
    {
        stu->credit=credit;
        stu->weightScore=scoreAll/credit;
        stu->weightGrade=gradeAll/credit;
    }
    else
    {
        stu->credit=0;
        stu->weightScore=0;
        stu->weightGrade=0;
    }
}

int writeStudent(stuhead stu)
{
    if (stu->h->next==NULL)
    {
        printf("该链表内没有学生");
        return EOF;
    }
    pSNode p = stu->h->next;
    int flag=0;
    FILE *fp=fopen("student.txt","w");
    while (1)//循环写入单个学生
    {
        flag=fprintf(fp,"%ld ",p->stu->studentNumber);
        flag=fprintf(fp,"%s ",p->stu->studentName);
        flag=fprintf(fp,"%hd ",p->stu->age);
        flag=fprintf(fp,"%c ",p->stu->sex);
        flag=fprintf(fp,"%f ",p->stu->weightScore);
        flag=fprintf(fp,"%f ",p->stu->weightGrade);
        flag=fprintf(fp,"%hd ",p->stu->credit);
        flag=fprintf(fp,"%d ",p->stu->show);
        for (size_t i = 0; i <50; i++)
        {
            flag=fputc(p->stu->engageActivity[i],fp);
        }
        
        for (LessonScore *lesson=p->stu->score->next; lesson; lesson=lesson->next)//循环写入单个学生的课程
        {
            flag=fprintf(fp,"%d ",1);//未结束标志变量
            flag=fprintf(fp,"%ld ",lesson->lessonCode);
            flag=fprintf(fp,"%s ",lesson->lessonName);
            flag=fprintf(fp,"%s ",lesson->teacher);
            flag=fprintf(fp,"%hd ",lesson->credit);
            flag=fprintf(fp,"%hd ",lesson->socre);
            flag=fprintf(fp,"%c",lesson->time);
        }
        flag=fprintf(fp,"0");//输入结束标志
        p=p->next;
        if (p)
            flag=fprintf(fp,"\n");  //若还有下一个换行
        else
            break;
    }
    return flag;
}

int readStudent(stuhead stuh)
{
    int flag=0;
    FILE *fp=fopen("student.txt","r");
    lessonLink h=NULL;
    while (!feof(fp))
    {
        /* code */
        char name[10];
        long code;
        short age;
        char sex;
        KeyType key;
        PStu pstu=NULL;
        flag=fscanf(fp,"%ld",&code);
        
        key.studentNumber=code;
        {
            flag=fscanf(fp,"%s",name);
            flag=fscanf(fp,"%hd",&age);
            flag=fscanf(fp,"%c",&sex);
            flag=fscanf(fp,"%c",&sex);
            studentCreate(&pstu,name,code,age,sex);//新建学生节点
            pSNode pSnode = createStuNode(pstu);
            InsertStuLink(stuh->h,pSnode);//加入链表
            key.stu=pSnode;
            SearchResult result = SearchBTree(stuh->t, key);
            InsertBTree(&(stuh->t),result.position,key,result.p);//加入二叉树
            flag=fscanf(fp,"%f",&pstu->weightScore);
            flag=fscanf(fp,"%f",&pstu->weightGrade);
            flag=fscanf(fp,"%hd",&pstu->credit);
            flag=fscanf(fp,"%d",&pstu->show);
            pstu->engageActivity[0]=fgetc(fp);
            for (size_t i = 0; i <50; i++)
            {
                pstu->engageActivity[i]=fgetc(fp);
            }
            for (char i = fgetc(fp); i=='1'; i = fgetc(fp))//
            {
                /* code */
                long lessonCode;
                short score;
                char time;
                char lessonName[10];
                short credit;
                char teacher[10];
                flag=fscanf(fp,"%ld",&lessonCode);
                flag=fscanf(fp,"%s",lessonName);
                flag=fscanf(fp,"%s",teacher);
                flag=fscanf(fp,"%hd",&credit);
                flag=fscanf(fp,"%hd",&score);
                flag=fscanf(fp,"%c",&time);
                flag=fscanf(fp,"%c",&time);
                h =pstu->score;
                LessonScore *p,*q;//p是插入位置，q是创建的节点指针
                searchLesson(h,lessonCode,&p);
                createLessonNode(&q,lessonCode,score,time,lessonName,credit,teacher);
                lessonBackInsert(p,q);
            }
            fgetc(fp);//吸收\n或到尾端
        }    
    }
    return flag;
}

void testS()
{
    stuhead sh;
    studentHeadInital(&sh);
    readStudent(sh);
    initalActRec();
    readActRec();
    for (size_t i = 0; i < 2; i++)
    {
        /* code */
        printf("当前链表\n");
        PrintAllstudent(sh->h);
        printf("当前树\n");
        PrintBTree(sh->t);
        newStudent(sh);
    }
    for (size_t i = 0; i < 3; i++)
    {
        /* code */
        printf("当前链表\n");
        PrintAllstudent(sh->h);
        printf("当前树\n");
        PrintBTree(sh->t);
        int i[3]={1,1,1};
        changeStu(sh,i);
    }
    printf("当前链表\n");
        PrintAllstudent(sh->h);
        printf("当前树\n");
        PrintBTree(sh->t);
    writeStudent(sh);
    
    
}