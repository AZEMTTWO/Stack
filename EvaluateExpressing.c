#include<stdio.h>
#include<stdlib.h>

#define  ERROR 0;
#define OK 1;

typedef int Status;
typedef int SElemType; //栈的元素类型

typedef struct Stack
{
	SElemType *top; //栈顶指针
	SElemType *base; //栈底指针
	int stacksize; //栈长
}Stack;

Stack OPTR; //运算符栈 
Stack OPND; //运算数栈 

/*函数声明*/

Status InitStack(Stack *S); /*初始化栈*/

Status Push(Stack *S,SElemType e); /*入栈*/

Status Pop(Stack *S,SElemType *e); /*出栈*/

Status GetTop(Stack S); /*得到栈顶元素*/

Status In(SElemType c); /*判断是否为运算符 */

Status Precode(SElemType o,SElemType p); /*运算符优先级判断*/

Status Operate(SElemType a,SElemType theta,SElemType b); /*计算*/

Status EvaluateExpression(); /*运算符优先级的求值算法*/

Status InitStack(Stack *S) /*初始化栈*/
{
	S->base = (SElemType *)malloc(sizeof(SElemType)*100); //动态分配
	if(!S->base) //内存分配失败
	return ERROR;
	S->top = S->base; //栈空标志
	S->stacksize = 100; //初始化栈长
	return OK;
}

Status Push(Stack *S,SElemType e) /*入栈*/
{
	if(S->top - S->base == S->stacksize) //栈已满
	{
		S->base = (SElemType *)realloc(S->base,(S->stacksize+10)*sizeof(SElemType)); //增加栈的空间大小
		if(!S->base) 
		return ERROR;
		S->top = S->base+S->stacksize; //更新栈顶
		S->stacksize = S->stacksize += 10;
	}
	*S->top++ = e; //将e插入栈顶 
	return OK;
}

Status Pop(Stack *S,SElemType *e) /*出栈*/
{
	if(S->top > S->base) //栈空标志
	{
		*e = *--S->top; //e等于栈顶元素，并且栈顶位置向下移动
		return OK;
	}
	else
	return ERROR;
}

Status GetTop(Stack S) /*得到栈顶元素*/ 
{
	if(S.top != S.base)
	return  *(S.top-1);
}

Status In(SElemType c) /*判断是否为运算符 */ 
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

Status Precode(SElemType o,SElemType p) /*运算符优先级判断*/
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



Status Operate(SElemType a,SElemType theta,SElemType b) /*计算*/
{
	SElemType c = 0,m,n;
	a = a - 48; //将a对应的ASCII码值转成对应的十进制数
	b = b - 48; //将b对应的ASCII码值转成对应的十进制数
	switch(theta)
	{
		case '+' : c = a + b + 48;break;

		case '-' : c = a - b + 48;break;

		case '*' : c = a * b + 48;break;

		case '/' : c = a / b + 48;break; 
	}
	return c;
}

Status EvaluateExpression() /*运算符优先级的求值算法*/
{
	SElemType c,x,a,b,theta;
	InitStack(&OPTR); //初始化运算符栈 
	Push(&OPTR,'#'); //起始‘#’入栈
	InitStack(&OPND); //初始化运算数栈 
	c = getchar();
	x = GetTop(OPTR);
	while(c != '#'||x != '#') //运算停止标志
	{
		if(In(c)) //若为运算符
		{
			switch (Precode(x,c)) //与栈顶比较优先级
			{
				case '<' :  //栈顶运算符优先级低则c入运算符栈
				Push(&OPTR,c);
				c = getchar();
				break;

				case '=' :  //脱括号接收下一字符
				Pop(&OPTR,&x);
				c = getchar();
				break;

				case '>' : //栈顶运算符优先级高则退栈并将运算结果压入运算数栈
				Pop(&OPTR,&theta);
				Pop(&OPND,&b);
				Pop(&OPND,&a);
				Push(&OPND,Operate(a,theta,b));
				break;
			}
		}

		else if(c >= '0'&&c <= '9') //若为运算数
		{
			Push(&OPND,c); //入运算数栈
			c = getchar();
		}

		else
		{
			printf("非法字符！\n");
			exit(0);
		}	
		x = GetTop(OPTR);
	}
	return GetTop(OPND);
}

int main(void)
{
    printf("请输入算术表达式,并以#结束,如2*(5-1)\n");   
    printf("%c",EvaluateExpression());  
    return 0; 
}
