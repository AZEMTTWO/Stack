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
  	int x; //横向坐标 
  	int y; //纵向坐标 
}PosType;

typedef struct 
{  
  	int ord; //通道块在迷宫路径上的序号 
  	PosType seat; //通道块的坐标位置 
  	int di; //下一方向 
}SElemType;

typedef struct  
{ 
	SElemType *base; //栈底指针 
   	SElemType *top; //栈顶指针 
   	int stacksize; //栈长 
}SqStack;

typedef struct
{
  int x;
  int y;
  char a[10][10]; //迷宫大小 
}MazeType; //迷宫类型

Status InitStack(SqStack *S); /*初始化一个栈*/

Status Push(SqStack *S,SElemType n); /*入栈*/

Status Pop(SqStack *S); /*出栈*/ 

Status StackEmpty(SqStack *S); /*栈空*/

Status InitMaze(MazeType *maze); /*初始化迷宫*/

Status Pass(MazeType *maze,PosType p); /*判断当前位置可否通过*/

Status FootPrint(MazeType *maze,PosType p); /*可通则留下足迹*/

PosType NextPos(PosType p,int i); /*探索下一位置并返回下一位置的坐标*/

Status MarkPrint(MazeType *maze,PosType p); /*曾走过但不通留下标记并返回OK*/

Status MazePath(MazeType *maze,PosType start,PosType end); /*迷宫maze若存在从入口start到end
                                                             的通道则求得一条存放在栈中*/

Status PrintMaze(MazeType *maze); /*输出迷宫*/

Status InitStack(SqStack *S) /*初始化一个栈*/
{
	S->base = (SElemType *)malloc(sizeof(SElemType)*100); //给栈分配大小为100的初始空间
	if(!S->base) //当分配失败时
		exit(1);
	S->top = S->base; //将base置于栈顶
	S->stacksize = 100; //定义栈S的长度为100
	return OK;
}

Status Push(SqStack *S,SElemType n) /*入栈*/ 
{
	if(S->top - S->base >= S->stacksize) //栈满，追加空间
	{
		S->base = (SElemType *)realloc(S->base,(S->stacksize+10)*sizeof(SElemType));//realloc对malloc申请的内存进行大小的调整
				  //给一个已经分配了地址的指针重新分配空间,参数S.base为原有的栈底地址,之后的sizeof是重新申请的地址长度1
		if(!S->base)
			exit(1);
		S->top = S->base + S->stacksize; //更新栈顶
		S->stacksize += 10; //增加栈的大小
	}
	*S->top++ = n; //给栈顶元素赋值，栈顶位置上移
	return OK;
}

Status Pop(SqStack *S) /*出栈*/ 
{
	SElemType e;
	if(S->top == S->base)
	return ERROR;
	e = *--S->top; //e等于栈顶元素，并且栈顶位置下移
	return OK;
}

Status StackEmpty(SqStack *S) /*栈空*/ 
{
    if(S->top==S->base) //栈空标志
        return TRUE;
	else
        return FALSE;
}

Status InitMaze(MazeType *maze) /*初始化迷宫*/ 
{ 
    int i,j;        
    maze->x=8;maze->y=8; //迷宫行和列数
    for(i=0;i<10;i++)
	{//迷宫行外墙
        maze->a[0][i]='#';
        maze->a[9][i]='#';
    }
    for(i=0;i<10;i++)
	{//迷宫列外墙
    	maze->a[i][0]='#';
        maze->a[i][9]='#';
    }
    for(i=1;i<9;i++)
        for(j=1;j<9;j++)
            maze->a[i][j]='1';//初始化迷宫
  //设定通道块上的不通的路块 
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

Status Pass(MazeType *maze,PosType p) /*判断当前位置可否通过*/
{
     if(maze->a[p.x][p.y]=='1') //可通
        return TRUE;
    else
        return FALSE;
}

Status FootPrint(MazeType *maze,PosType p) /*可通则留下足迹*/ 
{
    maze->a[p.x][p.y]='*'; //"*"表示可通
    return OK;

}

PosType NextPos(PosType p,int i) /*探索下一位置并返回下一位置的坐标*/
{
    PosType q;
    q=p;
    switch(i)
	{   //1,2,3,4分别表示东,南,西,北方向
        case 1 : q.y+=1; break;
        case 2 : q.x+=1; break;
        case 3 : q.y-=1; break;
        case 4 : q.x-=1; break;
        default: exit(ERROR);  
	}
    return q;
}

Status MarkPrint(MazeType *maze,PosType p) /*曾走过但不通留下标记并返回OK*/
{
    maze->a[p.x][p.y]='@';//"@"表示曾走过但不通
    return OK;
}

Status MazePath(MazeType *maze,PosType start,PosType end)/*迷宫maze若存在从入口start到end
                                                             的通道则求得一条存放在栈中*/
{    
    SqStack S;
	PosType p;
    int pstep; //当前序号
    SElemType e;
    InitStack(&S);
    p=start; //设置"当前位置"为"入口位置"
    pstep=1;   //探索第一步
    do{   
        if(Pass(&(*maze),p))
		{     //当前位置可以通过,
        	FootPrint(&(*maze),p);//留下足迹	 
            e.ord=pstep;
            e.seat=p;
            e.di=1;
            Push(&S,e);              //加入路径
            if(p.x == end.x&& p.y == end.y)
      		return TRUE; //到达出口             
            p=NextPos(p,1); //下一位置是当前位置的东邻
            pstep++;       //探索下一步                            
        }
        else
		{        //当前位置不通
            if(!StackEmpty(&S))
			{     
				Pop(&S);
                while(e.di==4 && !StackEmpty(&S))
				{
                    MarkPrint(&(*maze),e.seat); //留下不能通过的标记,并退一步
					Pop(&S);    
                    e.di=S.top->di;
					e.seat=S.top->seat;
					e.ord=S.top->ord;	   
            	}
                if(e.di< 4)
				{               
					e.di++;//换下一个方向探索
                    Push(&S,e);            
                    p=NextPos(e.seat,e.di);//设定当前位置是该新方向上的相邻
                }
            }
        }
    }while(!StackEmpty(&S));
   	return OK;
}


int PrintMaze(MazeType *maze)
{ 
    int i,j;
   	printf("用*代表迷宫的从入口到出口的一条路径\n");
   	printf("用#代表墙和不通的地方,用@代表曾走过的通道块但不通\n");
   	printf("用1代表可以通过的通道块\n");
   	printf("  ");
    printf("\n");
    for(i=0;i<10;i++)
	{
        for(j=0;j<10;j++)
            printf("%4c",maze->a[i][j]);//输出迷宫          
        printf("\n");
    }
}

int main(void)
{ 
  	MazeType maze;
  	PosType start,end;
    InitMaze(&maze); //初始化并创建迷宫
  	start.x=1;start.y=1; //迷宫入口坐标
  	end.x=8;end.y=8; //迷宫出口坐标
    PrintMaze(&maze);
    MazePath(&maze,start,end);
    PrintMaze(&maze); //打印路径
}

