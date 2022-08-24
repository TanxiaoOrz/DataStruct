#include "bTree.h"
#include <stdlib.h>
#include <stdio.h>

int order=orderNow;
int keyMax=orderNow-1; //最大关键字数量
int keymin=(orderNow-1)/2; //最小关键字数量

int InitBTree(BTree *t)//初始化树
{
    *t=NULL;
    return 0;
}

void InitBTreeNode(BTreeNode **p)//初始化节点
{
    *p =(BTreeNode*) malloc(sizeof(BTreeNode));
    (*p)->keyNumber=0;
    (*p)->parent=NULL;
    for (size_t i = 0; i <= keyMax+1; i++)
    {
        (*p)->kid[i]=NULL;
    }
    
}

int SearchBTNode(BTreeNode *p,KeyType k){//查找关键字k的插入位置i 

    int i=0;
    for(i=0;(i<p->keyNumber)&&((p->key[i].studentNumber)<k.studentNumber);i++);
    return i;
}

SearchResult SearchBTree(BTree t,KeyType k)//查找关键字，返回SearchResult结构体
{


    BTreeNode *parent=NULL,*waitSearch=t;           //waitSearch指向待查结点,parent指向waitsearcch的双亲
    int found=0;                                //设定查找成功与否标志 
    int i=0;                 
    SearchResult r;                                       //设定返回的查找结果 

    while(waitSearch!=NULL&&found==0){
        i=SearchBTNode(waitSearch,k);                        //在结点p中查找关键字k,使得p->key[i]<=k<p->key[i+1]
        if(i>=0&&waitSearch->key[i].studentNumber==k.studentNumber)                       //找到待查关键字
            found=1;                            //查找成功 
        else{                                       //查找失败 
            parent=waitSearch;                            
            waitSearch=waitSearch->kid[i];
        }
    }

    if(found==1){                               //查找成功
        r.p=waitSearch;
        r.position=i;
        r.flag='Y';
    }
    else{                                           //查找失败
        r.p=parent;
        r.position=i;
        r.flag='N';
    }

    return r;                                       //返回关键字k的位置(或插入位置)
}

void InsertBTNode(BTreeNode **p,int i,KeyType k,BTreeNode *q)
{
//将关键字k和结点q分别插入到p->key[i]和p->ptr[i+1]中
    int j;
    for(j=(*p)->keyNumber-1;j>=i;j--){                      
        (*p)->key[j+1]=(*p)->key[j];//关键字后
        (*p)->kid[j+2]=(*p)->kid[j+1];//孩子后
    }
    (*p)->key[i]=k;
    (*p)->kid[i+1]=q;
    if(q!=NULL) //如果是叶子节点
        q->parent=*p;
    (*p)->keyNumber++;
}

void SplitBTNode(BTreeNode **p,BTreeNode **q)
{
//将结点p分裂成两个结点,前一半保留,后一半移入结点q
    int i;
    int s=keymin+1;//保留最小数量+1在p,key[x]留给父节点
    InitBTreeNode(q);             //创建结点q

    //(*q)->kid[0]=(*p)->kid[s];                            //后一半移入结点q
    for(i=s;i<order+1;i++){
        (*q)->key[i-s]=(*p)->key[i];
        (*q)->kid[i-s]=(*p)->kid[i];
    }
    
    (*q)->keyNumber=(*p)->keyNumber-s;                
    (*q)->parent=(*p)->parent;
    for(i=0;i<=(*q)->keyNumber;i++)                     //修改双亲指针 
        if((*q)->kid[i]!=NULL) 
            (*q)->kid[i]->parent=*q;                    //修改子节点双亲
    (*p)->keyNumber=s-1;                                  //结点p的前一半保留,修改keyNumber
}

void NewRoot(BTreeNode **t,KeyType k,BTreeNode *kid0,BTreeNode *kid1)//生成新的根结点t,kid0和kid1为子树指针
{
    InitBTreeNode(t);             //分配空间 
    (*t)->keyNumber=1;
    (*t)->kid[0]=kid0;
    (*t)->kid[1]=kid1;
    (*t)->kid[2]=NULL;
    (*t)->key[0]=k;
    if(kid0!=NULL)                                     //调整子节点双亲指针 
        kid0->parent=*t;
    if(kid1!=NULL) 
        kid1->parent=*t;
    (*t)->parent=NULL;
}

void InsertBTree(BTree *t,int i,KeyType k,BTreeNode *p)//在树t上结点q的key[i]与key[i+1]之间插入关键字k。若引起结点过大,则沿双亲链进行必要的结点分裂调整,使t仍是B树
{

    BTreeNode *q;   //分裂节点时的存储指针和插入时的额外子节点指针
    int finish,newroot;                   //设定需要新结点标志和插入完成标志 
    KeyType x;
    if(p==NULL)                                     //t是空树
        NewRoot(t,k,NULL,NULL);                     //生成仅含关键字k的根结点t
    else{
        x=k;
        q=NULL;
        finish=0;       
        newroot=0;
        while(finish==0&&newroot==0){
            InsertBTNode(&p,i,x,q);              //将关键字x和结点q分别插入到p->key[i+1]和p->kid[i+1]
            if (p->keyNumber<=keyMax)           //检查上溢
                finish=1;                       //插入完成
            else{         
                SplitBTNode(&p,&q);                   //分裂结点 
                x=p->key[keyMax-1];
                if(p->parent){                      //查找x的插入位置
                    p=p->parent;
                    i=SearchBTNode(p, x);
                }
                else                                //没找到x，需要新结点 
                    newroot=1;
            }
        }
        if(newroot==1)                          //根结点已分裂为结点p和q 
            NewRoot(t,x,p,q);                       //生成新根结点t,p和q为子树指针
    }
}

int InitQueue(LinkList *L){
//初始化队列 
    *L=(LNode*)malloc(sizeof(LNode));                //分配结点空间 
    if(L==NULL)                                     //分配失败              
        return OVERFLOW;
     (*L)->next=NULL;
     return 1;
}


LNode* CreateNode(BTreeNode *p){
//新建一个结点 
    LNode *q;
    q=(LNode*)malloc(sizeof(LNode));                //分配结点空间
    if(q!=NULL){                                    //分配成功 
        q->data=p;
        q->next=NULL;
    }
   return q;
}


Status Enqueue(LNode *p,BTreeNode *q){ 
//元素q入队列
    if(p==NULL)                                     
        return ERROR;                               
    while(p->next!=NULL)                            //调至队列最后 
        p=p->next;
    p->next=CreateNode(q);                          //生成结点让q进入队列 
    return OK;
}


Status Dequeue(LNode *p,BTreeNode **q){
//出队列，并以q返回值 
    LNode *aq;
    if(p==NULL||p->next==NULL)                      //删除位置不合理 
        return ERROR; 
    aq=p->next;                                     //修改被删结点aq的指针域
    p->next=aq->next;                               
    *q=aq->data;
    free(aq);                                       //释放结点aq
    return OK;
}


Status IfEmpty(LinkList L){
//队列判空 
    if(L==NULL)                                     //队列不存在 
        return ERROR;
    if(L->next==NULL)                               //队列为空 
        return TRUE;
    return FALSE;                                   //队列非空 
}

void DestroyQueue(LinkList L){
//销毁队列 
   LinkList p;
    if(L!=NULL){
        p=L;
        L=L->next;
        free(p);                                    //逐一释放 
        DestroyQueue(L);
    }
}

int Traverse(BTree t,LinkList L,int newline,int sum){
//用队列遍历输出B树 
    int i;
    BTree p;
    if(t!=NULL){
        printf("  [ ");
                               //入队         
        for(i=0;i<t->keyNumber;i++){  
            Enqueue(L,t->kid[i]);
            printf(" %ld ",t->key[i].studentNumber);
            //                 //子结点入队 
        }
        Enqueue(L,t->kid[i]);
        sum+=t->keyNumber+1;
        printf("]");
        if(newline==0){                             //需要另起一行 
            printf("\n");
            newline=sum-1;
            sum=0;
        }
        else
            newline--;
     }

     if(IfEmpty(L)==FALSE){                         //l不为空 
         Dequeue(L,&p);                              //出队，以p返回 
         Traverse(p,L,newline,sum);                 //遍历出队结点 
     }
     return 1;
 }


int PrintBTree(BTree t){
//输出B树 
   LinkList L;
    if(t==NULL){
        printf("  B树为空树");
        return 1;
    }
    InitQueue(&L);                                   //初始化队列 
    Traverse(t,L,0,0);                              //利用队列输出 
    DestroyQueue(L);                                //销毁队列 
    return 1;
}


int test2()
{
    int i;
    KeyType k;
    k.stu=NULL;
    system("color 70");
    BTree t=NULL;  
    SearchResult s;                                       //设定查找结果 
    while(1){
    printf("此时的B树：\n");
    //PrintBTree(t); 
    printf("\n");
    printf("=============Operation Table=============\n");
    printf("   1.Init     2.Insert    3.Delete    \n");
    printf("   4.Destroy  5.Exit      \n");
    printf("=========================================\n");
    printf("Enter number to choose operation:_____\b\b\b");
    scanf("%d",&i);
    switch(i){
        case 1:{
            InitBTree(&t);
            printf("InitBTree successfully.\n");
            break;
        }


        case 2:{
            printf("Enter number to InsertBTree:_____\b\b\b");
            scanf("%ld",&(k.studentNumber));
            s=SearchBTree(t,k);
            InsertBTree(&t,s.position,k,s.p);
            printf("InsertBTree successfully.\n");
            PrintBTree(t);
            printf("\n");
            break;
        }
/*        case 3:{
            printf("Enter number to DeleteBTree:_____\b\b\b");
            scanf("%d",&k);
            BTreeDelete(t,k);
            printf("\n");
            printf("DeleteBTree successfully.\n");
            break;
        }
        case 4:{
            DestroyBTree(t);
            break;
            printf("DestroyBTree successfully.\n");
        }*/
        case 5:{
            exit(-1);               
            break;
        }
        case 6:{
            break;
        }
    }
 }

}

int test1()
{
    printf("test\n");
    KeyType k[6];
    

    BTreeNode t;
    BTreeNode t1;
    BTreeNode t2;
    for(int i=0;i<6;i++)
    {
        k[i].studentNumber=i*2;
        k[i].stu=NULL;
    }
    for(int i = 0; i < 3; i++)
    {
        /* code */
        t.kid[i]=NULL;
        t1.kid[i]=NULL;
        t2.kid[i]=NULL;
    }
    

    t.key[0]=k[2];
    t.keyNumber=1;
    t.kid[0]=&t1;
    t.kid[1]=&t2;
    t1.key[0]=k[0];
    t1.key[1]=k[1];
    t1.keyNumber=2;
    t2.key[0]=k[3];
    t2.key[1]=k[4];
    t2.keyNumber=2;
    
    
    
    PrintBTree(&t);
    system("pause");

    return 0;
}