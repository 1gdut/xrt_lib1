#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int main()
{
   LinkStack* linkStack = (LinkStack*)malloc(sizeof(LinkStack));
   int* length = (int*)malloc(sizeof(int));
   ElemType *e = (ElemType*)malloc(sizeof(ElemType));

   initLStack(linkStack);
   int i;
   for (i = 0; i < 5; i++) // 赋值
   {
      pushLStack(linkStack, i);
   }
   if (isEmptyLStack(linkStack) == 1)
   {
      printf("此链栈为空\\n");
   }
   else
   {
      printf("此链栈不为空\n");
   }
   printf("栈链的值有：");
   print(linkStack);
   printf("\n");
   LStackLength(linkStack, length);
   printf("链栈的长度是%d\n", *length); // 给出长度
   getTopLStack(linkStack, e);
   printf("栈顶的元素是%d\n",*e);
   clearLStack(linkStack);
   printf("清空后的栈：");
   print(linkStack);
   printf("\n");
   destroyLStack(linkStack);
   
   system("pause");
   return 0;
}

Status initLStack(LinkStack *s)
{
   s->count = 0;
   s->top = NULL;
   return 1;  
}

Status isEmptyLStack(LinkStack *s)
{
   if (s->top == NULL && s->count == 0)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

Status getTopLStack(LinkStack *s, ElemType *e)
{
   *e = s->top->data;//将栈顶的数据赋给*e
   return 1;
}

Status LStackLength(LinkStack *s, int *length)
{
   *length = s->count;
   return 1;
}

Status pushLStack(LinkStack *s, ElemType data)
{
   LinkStackPtr linkStackPtr = malloc(sizeof(StackNode)); // 新指针
   if (linkStackPtr == NULL)                              // 分配失败
   {
      return 0;
   }
   else
   {
      linkStackPtr->data = data;
      linkStackPtr->next = s->top; // 把新指针放在栈顶
      s->top = linkStackPtr;       // 再把栈顶移过去
      s->count++;                 // 长度加1
      return 1;
   }
}

Status popLStack(LinkStack *s, ElemType *data)
{
   LinkStackPtr linkStackPtr = s->top; // 栈顶，就是要出栈的
   *data = linkStackPtr->data;
   s->top = s->top->next; // 栈顶等于原栈顶的下一个
   free(linkStackPtr);
   return 1;
}

void print(LinkStack *linkStack)//打印链表
{
   LinkStackPtr linkStackPtr = linkStack->top;
   while (linkStackPtr != NULL)
   {
      printf("%d ", linkStackPtr->data);
      linkStackPtr = linkStackPtr->next;
   }
}

Status clearLStack(LinkStack *s)
{
	LinkStackPtr linkStackPtr;
   while (s->top)//top往下移，前一个free掉
   {
      linkStackPtr = s->top;
      s->top = s->top->next;
      s->count--;
      free(linkStackPtr);
   }
   return 1;
}

Status destroyLStack(LinkStack *s)//清空后把结点free掉
{
   clearLStack(s);
   free(s);
   return 1;
}
