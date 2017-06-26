#include "stdio.h"
#include "malloc.h"
#define SIZE 3
#ifndef FALSE
	#define FALSE 0
#endif
#ifndef TRUE
	#define TRUE 1
#endif
#define NONE 0
#define PLAYER_A 1
#define PLAYER_B 2
#define WARNNING 666 
#define COMPETITOR 200
#define WINNER -1
char chessboard[SIZE][SIZE];
struct CHESS_MAN
{
 int row;
 int col;
};
int get_value(int player)/*PLAYER可能胜利的方法*/
{
 int i,j,ret=0;
 int row,col,inc;
 int a=FALSE;
 for(i=0;i<SIZE;i++)/*检查所有行*/
 {
  row=SIZE;
  a=FALSE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]==player) row--;/*如果该位置有player的棋子占据*/
   if(chessboard[i][j]==NONE) a=TRUE;/*如果该位置还没有棋子占据，则返回a为TRUE*/
  }
  if(row==1&&a==TRUE) return WARNNING;/*电脑:该行中有一个空位且有对手下的2个旗子,则可能会输掉该局，返回WARNNING值）*/
  else if(row==SIZE) ret++;/*电脑:该行中没有player的棋子，ret+1*/
 }
 for(i=0;i<SIZE;i++)/*检查所有列*/
 {
  col=SIZE;
  a=FALSE;
  for(j=0;j<SIZE;j++)
  { 
   if(chessboard[j][i]==player) col--;/*如果该位置有player的棋子占据*/
   if(chessboard[j][i]==NONE) a=TRUE;/*如果该位置还没有棋子占据，则返回a为TRUE*/
  }
  if(col==1&&a==TRUE) return WARNNING;/*电脑:该列中有一个空位且有对手下的2个旗子,则可能会输掉该局，返回WARNNING值*/
  else if(col==SIZE) ret++;/*电脑:该列中没有player的棋子，ret+1*/
 }
 inc=SIZE;/*检查左对角线*/
 a=FALSE;
 for(i=0,j=0;i<SIZE;i++,j++)
 {
  if(chessboard[i][j]==player) inc--;/*如果该位置有player的棋子占据*/
  if(chessboard[i][j]==NONE) a=TRUE;/*如果该位置还没有棋子占据，则返回a为TRUE*/
 }
 if(inc==1&&a==TRUE) return WARNNING;/*电脑:左对角线中有一个空位且有对手下的2个旗子,可能会输掉该局，返回WARNNING值*/
 else if(inc==SIZE) ret++;/*电脑:左对角线中没有player的棋子，ret+1*/
 inc=SIZE;/*检查右对角线*/
 a=FALSE;
 for(i=0,j=SIZE-1;i<SIZE;i++,j--)
 {
  if(chessboard[i][j]==player) inc--;/*如果该位置有player的棋子占据*/
  if(chessboard[i][j]==NONE) a=TRUE;/*如果该位置还没有棋子占据，则返回a为TRUE*/
 }
 if(inc==1&&a==TRUE) return WARNNING;/*电脑:右对角线中有一个空位且有对手下的2个旗子,可能会输掉该局，返回WARNNING值*/
 else if(inc==SIZE) ret++;/*电脑:右对角线中没有player的棋子，ret+1*/
 return ret;
}; 
void disp_chess_board(void)/*显示棋盘图形边框*/
{
 int i,j;
 for(i=0;i<SIZE*4+1;i++)/*显示棋盘最顶层边框*/
  printf("-");
 printf("\n");
 for(i=0;i<SIZE;i++)/*显示3层棋盘格落子情况及其左、右和下边框*/
 {
  printf("|");
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]==PLAYER_A) printf(" o |");/*如果是PLAYER_A落子则用o表示棋子*/
   else if(chessboard[i][j]==PLAYER_B) printf(" x |");/*如果是PLAYER_B落子则用x表示棋子*/
   else printf("???|");
  }
  printf("\n");
  for(j=0;j<SIZE*4+1;j++)/*输出该层下边框*/
   printf("-");
  printf("\n");
 }
 return;
};
void init_chess_board(void)/*棋盘初始状况*/
{
	int i,j;
	for(i=0;i<SIZE;i++)
	for(j=0;j<SIZE;j++)
	chessboard[i][j]=NONE;
	return;
};
int enter_chess_man(int row, int col, int player)/*玩家落子*/
{
 if(row>=SIZE||col>=SIZE) return FALSE;/*输入位置超出棋盘坐标，不能落子*/
 if(chessboard[row][col]!=NONE) return FALSE;/*输入当该位置已有棋子占据，不能落子*/
 chessboard[row][col]=player;/*玩家落子*/
 return TRUE;
}
int chk_winner(int player)/*判断胜利状况*/
{
 int i,j;
 int col,row,inc;
 for(i=0;i<SIZE;i++)/*占满一行*/
 {
  row=TRUE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]!=player) row=FALSE;
  }
  if(row==TRUE) return TRUE;
 }
 for(i=0;i<SIZE;i++)/*占满一列*/
 {
  col=FALSE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[j][i]!=player) col=FALSE;
  }
  if(col==TRUE) return TRUE;
}
inc=TRUE;/*占满左对角线*/
j=0;
for(i=0;i<SIZE;i++)
{
 if(chessboard[i][i+j]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
inc=TRUE;/*占满右对角线*/
j=SIZE-1;
for(i=0;i<SIZE;i++)
{
 if(chessboard[i][j-i]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
  return FALSE;/*还没有一方胜利*/
};
int get_best_chess(struct CHESS_MAN *best_chess, int player, int other)/*最佳的一步棋*/
{
 int chess_value[9];
 struct CHESS_MAN chess[9];
 int i,j,cur=0;
for(i=0;i<SIZE;i++)
 {
  for(j=0;j<SIZE;j++)
   {
	chess[cur].row=i;
	chess[cur++].col=j;
   }
  }
for(i=0;i<9;i++)
  {
   if(enter_chess_man(chess[i].row,chess[i].col,player)==TRUE)
	{
	 chess_value[i]=get_value(other);
	 if(chk_winner(player)==TRUE) chess_value[i]=WINNER;/*玩家未胜利，则chess_value[i]为WINNER*/
	 chessboard[chess[i].row][chess[i].col]=NONE;/*玩家落子位置错误，棋盘为0*/
	}
	 else chess_value[i]=COMPETITOR;/* 玩家落子位置正确，*/
  }
  cur=0;
  for(i=0;i<9;i++)/*选择值为最低的chess_value*/
   {
	if(chess_value[cur]>chess_value[i]) cur=i;
   }
   best_chess->row=chess[cur].row;
   best_chess->col=chess[cur].col;
   return chess_value[cur];
};
int chk_full(void)/*检查是否还有未落子的棋格*/
{
 int i,j;
 for(i=0;i<SIZE;i++)
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]==NONE) return FALSE;
  }
 return TRUE;
};
int main(void)
{
 int i;
 struct CHESS_MAN best_chess;
 int player=PLAYER_A;/*玩家先手*/
 int competitor=PLAYER_B;/*电脑后手*/
 int bEND=FALSE; /*初始bEND的值*/
 int row,col; /*玩家输入所下棋子的位置*/
 init_chess_board();/*初始棋盘数据*/
 disp_chess_board();/*绘制棋盘边框*/
 while(bEND==FALSE)/*若bEND为FALSE，则判定棋局结束*/
 {
  if(player==PLAYER_A)
  {
   do/*轮到玩家下棋时，显示玩家坐标输入提示*/
   {
	printf("] 请输入您落子的位置 : \n");
	printf("] 行坐标为: ");
	scanf("%d",&row);
	printf("] 列坐标为: ");
	scanf("%d",&col);
	if(enter_chess_man(row-1,col-1,player)==TRUE)/*玩家落子正确，棋盘坐标显示，并结束该循环*/
    {
	 printf("] 您落子的位置是 [%d][%d]\n",row,col);
	 break;
	}
	else printf("] 您输入的棋盘坐标错误，请重新输入\n");/*玩家落子坐标错误提示*/
  }while(TRUE);
 }
 else
 {
  get_best_chess(&best_chess,player,competitor);/*电脑选择最佳位置下棋并显示落子的棋盘坐标提示*/
  enter_chess_man(best_chess.row,best_chess.col,player);
  printf("] 电脑落子的位置是[%d][%d]\n",best_chess.row+1,best_chess.col+1);
 }
 disp_chess_board();/*显示当前棋盘落子状况*/
 bEND=TRUE;/*判断胜负后，显示该棋局的胜利者提示*/
 if(chk_winner(player)) printf("] 胜利者是Player %d.\n",player);
 else if(chk_winner(competitor)) printf("] 胜利者是Player %d.\n",competitor);
 else if(chk_full()) printf("] 平局.\n");
 else bEND=FALSE;
competitor=player;
 if(player==PLAYER_A) player=PLAYER_B;
 else player=PLAYER_A; };
printf("\n\n本棋局结束.\n\n");/*该局已结束*/
return 0;
};
