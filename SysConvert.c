#include<stdio.h>
#include<stdlib.h>


# define OK 1
# define ERROR 0
# define Status int


typedef int ElemType;

typedef struct
{
	ElemType *base; //��ջ����֮ǰ������֮��base��ֵΪNULL
	ElemType *top; //ջ��ָ��
	int stacksize; //��ǰ�ѷ���Ĵ���ռ䣬��Ԫ��Ϊ��λ
}SqStack;
 
 SqStack S;
 
Status InitStack(SqStack *S); 
 
Status InitStack(SqStack *S)
{
	S->base = (ElemType *)malloc(sizeof(ElemType)*100); //��ջ�����СΪ100�ĳ�ʼ�ռ�
	if(!S->base) //������ʧ��ʱ
		exit(1);
	S->top = S->base; //��base����ջ��
	S->stacksize = 100; //����ջS�ĳ���Ϊ100
	return OK;
}

Status Push(SqStack *S,ElemType n)
{
		if(S->top - S->base >= S->stacksize) //ջ����׷�ӿռ�
	{
		S->base = (ElemType *)realloc(S->base,(S->stacksize+10)*sizeof(ElemType));//realloc��malloc������ڴ���д�С�ĵ���
				  //��һ���Ѿ������˵�ַ��ָ�����·���ռ�,����S.baseΪԭ�е�ջ�׵�ַ,֮���sizeof����������ĵ�ַ����1
		if(!S->base)
			exit(1);
		S->top = S->base + S->stacksize; //����ջ��
		S->stacksize += 10; //����ջ�Ĵ�С
	}
	*S->top++ = n; //��ջ��Ԫ�ظ�ֵ��ջ��λ������
	return OK;
}

Status Pop(SqStack *S,ElemType *e)
{
	if(S->top == S->base)
	return ERROR;
	*e = *--S->top; //e����ջ��Ԫ�أ�����ջ��λ������
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

Status main(void)  /*��ʮ����ת��Ϊ��Ӧ����*/
{
	InitStack(&S);
	int x,p,e;
	printf("������ʮ������x�Ͷ�Ӧ����p\n");
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
