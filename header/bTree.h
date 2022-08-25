#ifndef _bTree_H
#define _bTree_H

#include "Structure.h"

#define orderMax 10 //定义阶数最大值
#define orderNow 3 //现在阶数



typedef struct keyType //bTree中存储的关键字信息
{
    long studentNumber;//关键字值学号
    pSNode stu;//该学号对应的学生信息指针
}KeyType;

typedef struct bTreeNode//BTree的节点类型
{
    int keyNumber;//该节点中关键字数量
    KeyType key[orderNow];//关键字存储数组多一个方便上溢操作
    struct bTreeNode *parent;//双亲指针
    struct bTreeNode *kid[orderNow+1];//孩子指针数组
}BTreeNode,*BTree;

typedef struct LNode{               //链表和链表结点类型 
    BTree data;                     //数据域
    struct LNode *next;             //指针域
}LNode, *LinkList;

typedef enum status{               //枚举类型（依次递增） 
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

typedef struct searchResult
{
    /* data */
    BTreeNode *p;//结点指针
    char flag;//是否有结果,Y有结果，N没有结果
    int position;//所在位置
}SearchResult;


int InitBTree(BTree *t);// 初始化树

int SearchBTNode(BTreeNode *p,KeyType k);//节点中查找
SearchResult SearchBTree(BTree t,KeyType k);//查找关键字对应节点,找到返回值的flag为Y，没找到为N
void InsertBTNode(BTreeNode **p,int i,KeyType k,BTreeNode *q);//将关键字k和结点q分别插入到p->key[i+1]和p->ptr[i+1]中
void SplitBTNode(BTreeNode **p,BTreeNode **q);//将结点p分裂成两个结点,前一半保留,后一半移入结点q
void NewRoot(BTreeNode **t,KeyType k,BTreeNode *kid0,BTreeNode *kid1);//生成新的根结点t,原结点p和结点q为子树指针
void InsertBTree(BTree *t,int i,KeyType k,BTreeNode *p); //在树上溢，则分裂

void Remove(BTreeNode *p,int i);//删除节点指定关键字并前移
void Substitution(BTreeNode *p,int i); //查找被删关键字p->key[i](在非叶子结点中)的替代叶子结点(右子树中值最小的关键字) 
void MoveRight(BTreeNode *p,int i);/*将双亲结点p中的最后一个关键字移入右结点q中将左结点aq中的最后一个关键字移入双亲结点p中*/
void MoveLeft(BTreeNode *p,int i);/*将双亲结点p中的第一个关键字移入结点aq中，将结点q中的第一个关键字移入双亲结点p中*/
void Combine(BTreeNode *p,int i); /*将双亲结点p、右结点q合并入左结点aq，并调整双亲结点p中的剩余关键字的位置*/ 
void AdjustBTree(BTreeNode *p,int i);//删除结点p中的第i个关键字后,调整B树                                        
int FindBTNode(BTreeNode *p,KeyType k,int *i);//反映是否在结点p中是否查找到关键字k 
int BTNodeDelete(BTreeNode *p,KeyType k);//在结点p中查找并删除关键字k
void BTreeDelete(BTree *t,KeyType k);//在树h中查找并删除关键字k


int Traverse(BTree t,LinkList L,int newline,int sum);//队列遍历树
int PrintBTree(BTree t);//输出b树

#endif