#include<stdio.h>
#include<stdlib.h>

#define  ERROR 0;
#define OK 1;

typedef int Status;
typedef int SElemType; //ջ��Ԫ������

typedef struct Stack
{
	SElemType *top; //ջ��ָ��
	SElemType *base; //ջ��ָ��
	int stacksize; //ջ��
}Stack;

Stack OPTR; //�����ջ 
Stack OPND; //������ջ 

/*��������*/

Status InitStack(Stack *S); /*��ʼ��ջ*/

Status Push(Stack *S,SElemType e); /*��ջ*/

Status Pop(Stack *S,SElemType *e); /*��ջ*/

Status GetTop(Stack S); /*�õ�ջ��Ԫ��*/

Status In(SElemType c); /*�ж��Ƿ�Ϊ����� */

Status Precode(SElemType o,SElemType p); /*��������ȼ��ж�*/

Status Operate(SElemType a,SElemType theta,SElemType b); /*����*/

Status EvaluateExpression(); /*��������ȼ�����ֵ�㷨*/

Status InitStack(Stack *S) /*��ʼ��ջ*/
{
	S->base = (SElemType *)malloc(sizeof(SElemType)*100); //��̬����
	if(!S->base) //�ڴ����ʧ��
	return ERROR;
	S->top = S->base; //ջ�ձ�־
	S->stacksize = 100; //��ʼ��ջ��
	return OK;
}

Status Push(Stack *S,SElemType e) /*��ջ*/
{
	if(S->top - S->base == S->stacksize) //ջ����
	{
		S->base = (SElemType *)realloc(S->base,(S->stacksize+10)*sizeof(SElemType)); //����ջ�Ŀռ��С
		if(!S->base) 
		return ERROR;
		S->top = S->base+S->stacksize; //����ջ��
		S->stacksize = S->stacksize += 10;
	}
	*S->top++ = e; //��e����ջ�� 
	return OK;
}

Status Pop(Stack *S,SElemType *e) /*��ջ*/
{
	if(S->top > S->base) //ջ�ձ�־
	{
		*e = *--S->top; //e����ջ��Ԫ�أ�����ջ��λ�������ƶ�
		return OK;
	}
	else
	return ERROR;
}

Status GetTop(Stack S) /*�õ�ջ��Ԫ��*/ 
{
	if(S.top != S.base)
	return  *(S.top-1);
}

Status In(SElemType c) /*�ж��Ƿ�Ϊ����� */ 
{  
    switch(c)  
    {  
    case'+':  
    case'-':  
    case'*':  
    case'/':  
    case'(':  
    case')':  
    case'#':return 1;  
    default:return 0;  
    }  
}  

Status Precode(SElemType o,SElemType p) /*��������ȼ��ж�*/
{
	SElemType f;
	switch(p)
	{
	case '+' :
	case '-' :
		if(o == '#'||o == '(')
			f = '<';
	else
		f = '>';
	break;

	case '*' :
	case '/' :
		if(o == '*'||o == '/'||o == ')')
			f = '>';
		else
			f = '<';
	break;

	case '(' :
		if(o == ')')
		{
			printf("1ERROR\n");
			exit(0);
		}
		else
			f = '<';
	break;

	case ')':
		switch(o)
		{
		case '(' :
			f = '=';
		break;
				
		case '#' :
			printf("2ERROR\n");
			exit(0);
		break;
		
		default : 
			f = '>';
		}
	break;

	case '#' :

		switch(o)
		{
		case '#' :
			f = '=';
		break;

		case '(' :
			printf("3ERROR\n");
			exit(0);

		default :
			f = '>';
		}
	}
	return f;
}



Status Operate(SElemType a,SElemType theta,SElemType b) /*����*/
{
	SElemType c = 0,m,n;
	a = a - 48; //��a��Ӧ��ASCII��ֵת�ɶ�Ӧ��ʮ������
	b = b - 48; //��b��Ӧ��ASCII��ֵת�ɶ�Ӧ��ʮ������
	switch(theta)
	{
		case '+' : c = a + b + 48;break;

		case '-' : c = a - b + 48;break;

		case '*' : c = a * b + 48;break;

		case '/' : c = a / b + 48;break; 
	}
	return c;
}

Status EvaluateExpression() /*��������ȼ�����ֵ�㷨*/
{
	SElemType c,x,a,b,theta;
	InitStack(&OPTR); //��ʼ�������ջ 
	Push(&OPTR,'#'); //��ʼ��#����ջ
	InitStack(&OPND); //��ʼ��������ջ 
	c = getchar();
	x = GetTop(OPTR);
	while(c != '#'||x != '#') //����ֹͣ��־
	{
		if(In(c)) //��Ϊ�����
		{
			switch (Precode(x,c)) //��ջ���Ƚ����ȼ�
			{
				case '<' :  //ջ����������ȼ�����c�������ջ
				Push(&OPTR,c);
				c = getchar();
				break;

				case '=' :  //�����Ž�����һ�ַ�
				Pop(&OPTR,&x);
				c = getchar();
				break;

				case '>' : //ջ����������ȼ�������ջ����������ѹ��������ջ
				Pop(&OPTR,&theta);
				Pop(&OPND,&b);
				Pop(&OPND,&a);
				Push(&OPND,Operate(a,theta,b));
				break;
			}
		}

		else if(c >= '0'&&c <= '9') //��Ϊ������
		{
			Push(&OPND,c); //��������ջ
			c = getchar();
		}

		else
		{
			printf("�Ƿ��ַ���\n");
			exit(0);
		}	
		x = GetTop(OPTR);
	}
	return GetTop(OPND);
}

int main(void)
{
    printf("�������������ʽ,����#����,��2*(5-1)\n");   
    printf("%c",EvaluateExpression());  
    return 0; 
}
