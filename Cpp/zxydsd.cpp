#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100   //MAXSIZE

//二叉树节点类型 
typedef struct node
{
char data;  //节点数据域 
struct node *lchild; //左孩子
struct node *rchild; //右孩子 
}node,*tree; 

//若定义二悥链表类型惎BiTree，则栈的数据元素类型SElemType为BiTree类型
typedef tree ElemType;

//栈的定义
typedef struct 
{
ElemType *base;  //栈底指针 
ElemType *top;  //栈顶指针 
int size;   //栈元素空间大小，相当于maxleng 
}sqstack;   //sqstack为结构类型
 
//初始化栈
void creat(sqstack &s)
{
s.base=new ElemType[MAXSIZE];
s.top=s.base;
s.size=MAXSIZE;  //空间 
 } 

//进栈
int push(sqstack &s,ElemType e)
{
if(s.top-s.base==s.size)  //判断是否栈满
return  0;
*s.top++=e;   //将元素e压入栈顶，栈顶指针加1
return 1; 
}

//出栈
int pop(sqstack &s,ElemType &e)
{
    if(s.top==s.base)  return -1;
e=*--s.top;   //栈顶指针减1
return 0;
} 

// 判断栈是否为空
int stackempty(sqstack s)
{
if(s.base==s.top)
return 0;
else return 1;
}

// 初始化二叉树，按先序遍历顺序建立二叉链表
void creattree(tree &T)
{
char ch;
ch=getchar();
if(ch=='#')  T=NULL;
else
{
T=new node;  
T->data=ch;    //根节点数据域置为 ch
creattree(T->lchild);
creattree(T->rchild); 
}
 } 



// 非递归方式中序遍历二叉树
void zhong(tree T)
{
sqstack s; //定义一个栈 
tree p,q; 
creat(s); //初始化一个空栈
p=T;  //指针p指向根节点 
q=new node;   //申请一个节点空间q，用来存放栈顶弹出的元素 
while(p||!stackempty(s))
{
if(p)  //p非空
{
push(s,p);   //根指针进栈
p=p->lchild;  //根指针进栈,遍历左子树 
}
else
{
pop(s,q);   //退栈
printf("%c",q->data);  //访问根节点
//cout<<q->data;
p=q->rchild;  //遍历右子树 
} 
}
}


int main()
{
tree T;   //二叉树节点
creattree(T);  //创建二叉树
printf("二叉树非递归算法的中序遍历序列：");
zhong(T); //中序遍历并输出结果
return 0; 
 
}