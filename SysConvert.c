#include<stdio.h>
#include<stdlib.h>


# define OK 1
# define ERROR 0
# define Status int


typedef int ElemType;

typedef struct
{
	ElemType *base; //在栈创建之前和销毁之后，base的值为NULL
	ElemType *top; //栈顶指针
	int stacksize; //当前已分配的储存空间，以元素为单位
}SqStack;
 
 SqStack S;
 
Status InitStack(SqStack *S); 
 
Status InitStack(SqStack *S)
{
	S->base = (ElemType *)malloc(sizeof(ElemType)*100); //给栈分配大小为100的初始空间
	if(!S->base) //当分配失败时
		exit(1);
	S->top = S->base; //将base置于栈顶
	S->stacksize = 100; //定义栈S的长度为100
	return OK;
}

Status Push(SqStack *S,ElemType n)
{
		if(S->top - S->base >= S->stacksize) //栈满，追加空间
	{
		S->base = (ElemType *)realloc(S->base,(S->stacksize+10)*sizeof(ElemType));//realloc对malloc申请的内存进行大小的调整
				  //给一个已经分配了地址的指针重新分配空间,参数S.base为原有的栈底地址,之后的sizeof是重新申请的地址长度1
		if(!S->base)
			exit(1);
		S->top = S->base + S->stacksize; //更新栈顶
		S->stacksize += 10; //增加栈的大小
	}
	*S->top++ = n; //给栈顶元素赋值，栈顶位置上移
	return OK;
}

Status Pop(SqStack *S,ElemType *e)
{
	if(S->top == S->base)
	return ERROR;
	*e = *--S->top; //e等于栈顶元素，并且栈顶位置下移
	return OK;
}

Status StackEmpty(SqStack S)
{
	while(S.top != S.base)
	{
		return OK;
	}
	return ERROR;
} 

Status main(void)  /*将十进制转换为对应进制*/
{
	InitStack(&S);
	int x,p,e;
	printf("请输入十进制数x和对应进制p\n");
	scanf("%d %d",&x,&p);
	while(x)
	{
		Push(&S,x%p);
		x = x/p;
	}
	while(StackEmpty(S))
	{
		Pop(&S,&e);
		printf("%d",e);
	}
}
