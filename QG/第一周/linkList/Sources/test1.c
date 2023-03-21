#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main()
{
    LinkedList L, L1, L2;
    ElemType *e;
    Status a = InitList(&L);//初始化
    if (a == SUCCESS)//判断是否成功
    {
        printf("初始化成功\n");
    }

    L->data = 0;
    L->next = L1;
    L1->data = 1;
    printf("%d\n", L->next);

    DestroyList(&L);
    printf("%d\n", L->next);//为0说明摧毁成功

    Status b =  InsertList(L1,L);
    if (b = SUCCESS)
    {
        printf("插入成功\n");
    }
    
    DeleteList(L,e);
    printf("%d\n",L->next);//为0说明成功
    system("pause");
    return 0;
}

Status InitList(LinkedList *L)
{
    if (*L == NULL)//判断是否创建成功
    {
        return ERROR;//否就返回error
    }
    else
    {
        *L = (LinkedList)malloc(sizeof(LNode)); //分配空间 
        (*L)->next = NULL;
        return SUCCESS;
    }
}

void DestroyList(LinkedList *L)
{
    LinkedList p = *L; // p此时指向头结点
    while ((*L)->next != NULL)//如果下一个结点不为空
    {
        *L = (*L)->next;
        free(p);//释放
        p = *L;
    }
}

Status InsertList(LNode *p, LNode *q) // q放p后面
{
    q->next = p->next;//原来p的下一个要放到q的下一个
    p->next = q;//然后p的下一个为q
    if (p->next = q)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

Status DeleteList(LNode *p, ElemType *e)
{
    LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    return SUCCESS;
}
