/*二叉树遍历操作*/
#include<iostream>
using namespace std;
typedef struct ERTree{
    int data;
    struct ERTree *lchild;
    struct ERTree *rchild;
};
ERTree tree;
