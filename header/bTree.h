#ifndef _bTree_H
#define _bTree_H



typedef struct keyType //bTree中存储的关键字信息
{
    long studentNumber;//关键字值学号
    Student *stu;//该学号对应的学生信息指针
}KeyType;

typedef struct bTreeNode//BTree的节点类型
{
    int keyNumber;//该节点中关键字数量
    KeyType key[2];//关键字存储数组
    struct bTreeNode *parent;//双亲指针
    struct bTreeNode *kid[3];//孩子指针数组
}BTreeNode,*BTree;



#endif