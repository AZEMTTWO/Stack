#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1
#define ERROR 0


typedef int Status;

typedef struct
{
  	int x; //�������� 
  	int y; //�������� 
}PosType;

typedef struct 
{  
  	int ord; //ͨ�������Թ�·���ϵ���� 
  	PosType seat; //ͨ���������λ�� 
  	int di; //��һ���� 
}SElemType;

typedef struct  
{ 
	SElemType *base; //ջ��ָ�� 
   	SElemType *top; //ջ��ָ�� 
   	int stacksize; //ջ�� 
}SqStack;

typedef struct
{
  int x;
  int y;
  char a[10][10]; //�Թ���С 
}MazeType; //�Թ�����

Status InitStack(SqStack *S); /*��ʼ��һ��ջ*/

Status Push(SqStack *S,SElemType n); /*��ջ*/

Status Pop(SqStack *S); /*��ջ*/ 

Status StackEmpty(SqStack *S); /*ջ��*/

Status InitMaze(MazeType *maze); /*��ʼ���Թ�*/

Status Pass(MazeType *maze,PosType p); /*�жϵ�ǰλ�ÿɷ�ͨ��*/

Status FootPrint(MazeType *maze,PosType p); /*��ͨ�������㼣*/

PosType NextPos(PosType p,int i); /*̽����һλ�ò�������һλ�õ�����*/

Status MarkPrint(MazeType *maze,PosType p); /*���߹�����ͨ���±�ǲ�����OK*/

Status MazePath(MazeType *maze,PosType start,PosType end); /*�Թ�maze�����ڴ����start��end
                                                             ��ͨ�������һ�������ջ��*/

Status PrintMaze(MazeType *maze); /*����Թ�*/

Status InitStack(SqStack *S) /*��ʼ��һ��ջ*/
{
	S->base = (SElemType *)malloc(sizeof(SElemType)*100); //��ջ�����СΪ100�ĳ�ʼ�ռ�
	if(!S->base) //������ʧ��ʱ
		exit(1);
	S->top = S->base; //��base����ջ��
	S->stacksize = 100; //����ջS�ĳ���Ϊ100
	return OK;
}

Status Push(SqStack *S,SElemType n) /*��ջ*/ 
{
	if(S->top - S->base >= S->stacksize) //ջ����׷�ӿռ�
	{
		S->base = (SElemType *)realloc(S->base,(S->stacksize+10)*sizeof(SElemType));//realloc��malloc������ڴ���д�С�ĵ���
				  //��һ���Ѿ������˵�ַ��ָ�����·���ռ�,����S.baseΪԭ�е�ջ�׵�ַ,֮���sizeof����������ĵ�ַ����1
		if(!S->base)
			exit(1);
		S->top = S->base + S->stacksize; //����ջ��
		S->stacksize += 10; //����ջ�Ĵ�С
	}
	*S->top++ = n; //��ջ��Ԫ�ظ�ֵ��ջ��λ������
	return OK;
}

Status Pop(SqStack *S) /*��ջ*/ 
{
	SElemType e;
	if(S->top == S->base)
	return ERROR;
	e = *--S->top; //e����ջ��Ԫ�أ�����ջ��λ������
	return OK;
}

Status StackEmpty(SqStack *S) /*ջ��*/ 
{
    if(S->top==S->base) //ջ�ձ�־
        return TRUE;
	else
        return FALSE;
}

Status InitMaze(MazeType *maze) /*��ʼ���Թ�*/ 
{ 
    int i,j;        
    maze->x=8;maze->y=8; //�Թ��к�����
    for(i=0;i<10;i++)
	{//�Թ�����ǽ
        maze->a[0][i]='#';
        maze->a[9][i]='#';
    }
    for(i=0;i<10;i++)
	{//�Թ�����ǽ
    	maze->a[i][0]='#';
        maze->a[i][9]='#';
    }
    for(i=1;i<9;i++)
        for(j=1;j<9;j++)
            maze->a[i][j]='1';//��ʼ���Թ�
  //�趨ͨ�����ϵĲ�ͨ��·�� 
  	maze->a[1][3]='#';maze->a[1][7]='#';
  	maze->a[2][3]='#';maze->a[2][7]='#';
  	maze->a[3][5]='#';maze->a[3][6]='#';
  	maze->a[4][2]='#';maze->a[4][3]='#';
  	maze->a[4][4]='#';maze->a[5][4]='#';
  	maze->a[6][2]='#';maze->a[6][6]='#';
  	maze->a[7][2]='#';maze->a[7][3]='#';
  	maze->a[7][4]='#';maze->a[7][6]='#';
  	maze->a[7][7]='#';maze->a[8][1]='#';
	return OK;

}

Status Pass(MazeType *maze,PosType p) /*�жϵ�ǰλ�ÿɷ�ͨ��*/
{
     if(maze->a[p.x][p.y]=='1') //��ͨ
        return TRUE;
    else
        return FALSE;
}

Status FootPrint(MazeType *maze,PosType p) /*��ͨ�������㼣*/ 
{
    maze->a[p.x][p.y]='*'; //"*"��ʾ��ͨ
    return OK;

}

PosType NextPos(PosType p,int i) /*̽����һλ�ò�������һλ�õ�����*/
{
    PosType q;
    q=p;
    switch(i)
	{   //1,2,3,4�ֱ��ʾ��,��,��,������
        case 1 : q.y+=1; break;
        case 2 : q.x+=1; break;
        case 3 : q.y-=1; break;
        case 4 : q.x-=1; break;
        default: exit(ERROR);  
	}
    return q;
}

Status MarkPrint(MazeType *maze,PosType p) /*���߹�����ͨ���±�ǲ�����OK*/
{
    maze->a[p.x][p.y]='@';//"@"��ʾ���߹�����ͨ
    return OK;
}

Status MazePath(MazeType *maze,PosType start,PosType end)/*�Թ�maze�����ڴ����start��end
                                                             ��ͨ�������һ�������ջ��*/
{    
    SqStack S;
	PosType p;
    int pstep; //��ǰ���
    SElemType e;
    InitStack(&S);
    p=start; //����"��ǰλ��"Ϊ"���λ��"
    pstep=1;   //̽����һ��
    do{   
        if(Pass(&(*maze),p))
		{     //��ǰλ�ÿ���ͨ��,
        	FootPrint(&(*maze),p);//�����㼣	 
            e.ord=pstep;
            e.seat=p;
            e.di=1;
            Push(&S,e);              //����·��
            if(p.x == end.x&& p.y == end.y)
      		return TRUE; //�������             
            p=NextPos(p,1); //��һλ���ǵ�ǰλ�õĶ���
            pstep++;       //̽����һ��                            
        }
        else
		{        //��ǰλ�ò�ͨ
            if(!StackEmpty(&S))
			{     
				Pop(&S);
                while(e.di==4 && !StackEmpty(&S))
				{
                    MarkPrint(&(*maze),e.seat); //���²���ͨ���ı��,����һ��
					Pop(&S);    
                    e.di=S.top->di;
					e.seat=S.top->seat;
					e.ord=S.top->ord;	   
            	}
                if(e.di< 4)
				{               
					e.di++;//����һ������̽��
                    Push(&S,e);            
                    p=NextPos(e.seat,e.di);//�趨��ǰλ���Ǹ��·����ϵ�����
                }
            }
        }
    }while(!StackEmpty(&S));
   	return OK;
}


int PrintMaze(MazeType *maze)
{ 
    int i,j;
   	printf("��*�����Թ��Ĵ���ڵ����ڵ�һ��·��\n");
   	printf("��#����ǽ�Ͳ�ͨ�ĵط�,��@�������߹���ͨ���鵫��ͨ\n");
   	printf("��1�������ͨ����ͨ����\n");
   	printf("  ");
    printf("\n");
    for(i=0;i<10;i++)
	{
        for(j=0;j<10;j++)
            printf("%4c",maze->a[i][j]);//����Թ�          
        printf("\n");
    }
}

int main(void)
{ 
  	MazeType maze;
  	PosType start,end;
    InitMaze(&maze); //��ʼ���������Թ�
  	start.x=1;start.y=1; //�Թ��������
  	end.x=8;end.y=8; //�Թ���������
    PrintMaze(&maze);
    MazePath(&maze,start,end);
    PrintMaze(&maze); //��ӡ·��
}

