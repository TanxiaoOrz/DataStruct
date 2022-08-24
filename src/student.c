#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


void studentCreate(Student **s,char name[],long code,short age,char sex)
{
    (*s)=(Student*)malloc(sizeof(Student));
    (*s)->studentNumber=code;
    (*s)->age=age;
    (*s)->sex=sex;
    strcpy((*s)->studentName,name);
    (*s)->socreFlag=0;
    (*s)->weightGrade=0;
    (*s)->weightScore=0;
    (*s)->credit=0;
    (*s)->show=0;
    (*s)->showFlag=0;
    (*s)->score=NULL;
    for (size_t i = 0; i < 50; i++)
    {
        /* code */
        (*s)->engageActivity[i]=0;
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
    if (head=NULL)
    {
        printf("该链表内没有学生");
    }
    pSNode p = head;
    while(p!=NULL){
    	printstudent(p->stu);
    	p=p->next;
	}
	printf("\n");
} 

//删除指定元素
void deleteStuLink(pSNode del)
{
	pSNode p,n;
	p=del->prev;
    n=del->next;
    p->next=n;
    if (n!=NULL)
        n->prev-p;
    free(p->stu);
    free(p);
} 

void printstudent(PStu stu)
{

}