#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Treenode {
    char val;
    struct Treenode* l;
    struct Treenode* r;
} Tree;

Tree* creatTree() { // 返回创建好的二叉树的根节点
    char ch = getchar();
    if (ch == '#')
        return NULL;
    else {
        Tree* T = (Tree*)malloc(sizeof(Tree));
        T->val = ch;
        T->l = creatTree();
        T->r = creatTree();
        return T;
    }
}

typedef struct Stack {
    Tree* data[MAX];
    int top;
} SqStack;

SqStack S;

void InitStack(SqStack* S) {
    S->top = -1;
}

int push(SqStack* S, Tree* T) { // 返回是否成功入栈，0表示失败
    if (S->top == MAX - 1)
        return 0;
    S->data[++S->top] = T;
    return 1;
}

Tree* pop(SqStack* S) { // 返回出栈的元素指针，NULL表示失败
    if (S->top == -1)
        return NULL;
    return S->data[S->top--];
}

Tree* top(SqStack* S) { // 返回栈顶元素指针，NULL表示失败
    if (S->top == -1)
        return NULL;
    return S->data[S->top];
}

void DLR(Tree* T) {
    InitStack(&S);
    push(&S, T);
    while (S.top != -1) {
        Tree* node = pop(&S);
        printf("%c ", node->val);
        if (node->r)
            push(&S, node->r);
        if (node->l)
            push(&S, node->l);
    }
}

int main() {
    Tree* T = creatTree();
    printf("二叉树非递归算法的先序遍历序列：");
    DLR(T);
    return 0;
}
