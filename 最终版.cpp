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
int get_value(int player)/*PLAYER����ʤ���ķ���*/
{
 int i,j,ret=0;
 int row,col,inc;
 int a=FALSE;
 for(i=0;i<SIZE;i++)/*���������*/
 {
  row=SIZE;
  a=FALSE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]==player) row--;/*�����λ����player������ռ��*/
   if(chessboard[i][j]==NONE) a=TRUE;/*�����λ�û�û������ռ�ݣ��򷵻�aΪTRUE*/
  }
  if(row==1&&a==TRUE) return WARNNING;/*����:��������һ����λ���ж����µ�2������,����ܻ�����þ֣�����WARNNINGֵ��*/
  else if(row==SIZE) ret++;/*����:������û��player�����ӣ�ret+1*/
 }
 for(i=0;i<SIZE;i++)/*���������*/
 {
  col=SIZE;
  a=FALSE;
  for(j=0;j<SIZE;j++)
  { 
   if(chessboard[j][i]==player) col--;/*�����λ����player������ռ��*/
   if(chessboard[j][i]==NONE) a=TRUE;/*�����λ�û�û������ռ�ݣ��򷵻�aΪTRUE*/
  }
  if(col==1&&a==TRUE) return WARNNING;/*����:��������һ����λ���ж����µ�2������,����ܻ�����þ֣�����WARNNINGֵ*/
  else if(col==SIZE) ret++;/*����:������û��player�����ӣ�ret+1*/
 }
 inc=SIZE;/*�����Խ���*/
 a=FALSE;
 for(i=0,j=0;i<SIZE;i++,j++)
 {
  if(chessboard[i][j]==player) inc--;/*�����λ����player������ռ��*/
  if(chessboard[i][j]==NONE) a=TRUE;/*�����λ�û�û������ռ�ݣ��򷵻�aΪTRUE*/
 }
 if(inc==1&&a==TRUE) return WARNNING;/*����:��Խ�������һ����λ���ж����µ�2������,���ܻ�����þ֣�����WARNNINGֵ*/
 else if(inc==SIZE) ret++;/*����:��Խ�����û��player�����ӣ�ret+1*/
 inc=SIZE;/*����ҶԽ���*/
 a=FALSE;
 for(i=0,j=SIZE-1;i<SIZE;i++,j--)
 {
  if(chessboard[i][j]==player) inc--;/*�����λ����player������ռ��*/
  if(chessboard[i][j]==NONE) a=TRUE;/*�����λ�û�û������ռ�ݣ��򷵻�aΪTRUE*/
 }
 if(inc==1&&a==TRUE) return WARNNING;/*����:�ҶԽ�������һ����λ���ж����µ�2������,���ܻ�����þ֣�����WARNNINGֵ*/
 else if(inc==SIZE) ret++;/*����:�ҶԽ�����û��player�����ӣ�ret+1*/
 return ret;
}; 
void disp_chess_board(void)/*��ʾ����ͼ�α߿�*/
{
 int i,j;
 for(i=0;i<SIZE*4+1;i++)/*��ʾ�������߿�*/
  printf("-");
 printf("\n");
 for(i=0;i<SIZE;i++)/*��ʾ3�����̸���������������Һ��±߿�*/
 {
  printf("|");
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]==PLAYER_A) printf(" o |");/*�����PLAYER_A��������o��ʾ����*/
   else if(chessboard[i][j]==PLAYER_B) printf(" x |");/*�����PLAYER_B��������x��ʾ����*/
   else printf("???|");
  }
  printf("\n");
  for(j=0;j<SIZE*4+1;j++)/*����ò��±߿�*/
   printf("-");
  printf("\n");
 }
 return;
};
void init_chess_board(void)/*���̳�ʼ״��*/
{
	int i,j;
	for(i=0;i<SIZE;i++)
	for(j=0;j<SIZE;j++)
	chessboard[i][j]=NONE;
	return;
};
int enter_chess_man(int row, int col, int player)/*�������*/
{
 if(row>=SIZE||col>=SIZE) return FALSE;/*����λ�ó����������꣬��������*/
 if(chessboard[row][col]!=NONE) return FALSE;/*���뵱��λ����������ռ�ݣ���������*/
 chessboard[row][col]=player;/*�������*/
 return TRUE;
}
int chk_winner(int player)/*�ж�ʤ��״��*/
{
 int i,j;
 int col,row,inc;
 for(i=0;i<SIZE;i++)/*ռ��һ��*/
 {
  row=TRUE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[i][j]!=player) row=FALSE;
  }
  if(row==TRUE) return TRUE;
 }
 for(i=0;i<SIZE;i++)/*ռ��һ��*/
 {
  col=FALSE;
  for(j=0;j<SIZE;j++)
  {
   if(chessboard[j][i]!=player) col=FALSE;
  }
  if(col==TRUE) return TRUE;
}
inc=TRUE;/*ռ����Խ���*/
j=0;
for(i=0;i<SIZE;i++)
{
 if(chessboard[i][i+j]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
inc=TRUE;/*ռ���ҶԽ���*/
j=SIZE-1;
for(i=0;i<SIZE;i++)
{
 if(chessboard[i][j-i]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
  return FALSE;/*��û��һ��ʤ��*/
};
int get_best_chess(struct CHESS_MAN *best_chess, int player, int other)/*��ѵ�һ����*/
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
	 if(chk_winner(player)==TRUE) chess_value[i]=WINNER;/*���δʤ������chess_value[i]ΪWINNER*/
	 chessboard[chess[i].row][chess[i].col]=NONE;/*�������λ�ô�������Ϊ0*/
	}
	 else chess_value[i]=COMPETITOR;/* �������λ����ȷ��*/
  }
  cur=0;
  for(i=0;i<9;i++)/*ѡ��ֵΪ��͵�chess_value*/
   {
	if(chess_value[cur]>chess_value[i]) cur=i;
   }
   best_chess->row=chess[cur].row;
   best_chess->col=chess[cur].col;
   return chess_value[cur];
};
int chk_full(void)/*����Ƿ���δ���ӵ����*/
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
 int player=PLAYER_A;/*�������*/
 int competitor=PLAYER_B;/*���Ժ���*/
 int bEND=FALSE; /*��ʼbEND��ֵ*/
 int row,col; /*��������������ӵ�λ��*/
 init_chess_board();/*��ʼ��������*/
 disp_chess_board();/*�������̱߿�*/
 while(bEND==FALSE)/*��bENDΪFALSE�����ж���ֽ���*/
 {
  if(player==PLAYER_A)
  {
   do/*�ֵ��������ʱ����ʾ�������������ʾ*/
   {
	printf("] �����������ӵ�λ�� : \n");
	printf("] ������Ϊ: ");
	scanf("%d",&row);
	printf("] ������Ϊ: ");
	scanf("%d",&col);
	if(enter_chess_man(row-1,col-1,player)==TRUE)/*���������ȷ������������ʾ����������ѭ��*/
    {
	 printf("] �����ӵ�λ���� [%d][%d]\n",row,col);
	 break;
	}
	else printf("] ����������������������������\n");/*����������������ʾ*/
  }while(TRUE);
 }
 else
 {
  get_best_chess(&best_chess,player,competitor);/*����ѡ�����λ�����岢��ʾ���ӵ�����������ʾ*/
  enter_chess_man(best_chess.row,best_chess.col,player);
  printf("] �������ӵ�λ����[%d][%d]\n",best_chess.row+1,best_chess.col+1);
 }
 disp_chess_board();/*��ʾ��ǰ��������״��*/
 bEND=TRUE;/*�ж�ʤ������ʾ����ֵ�ʤ������ʾ*/
 if(chk_winner(player)) printf("] ʤ������Player %d.\n",player);
 else if(chk_winner(competitor)) printf("] ʤ������Player %d.\n",competitor);
 else if(chk_full()) printf("] ƽ��.\n");
 else bEND=FALSE;
competitor=player;
 if(player==PLAYER_A) player=PLAYER_B;
 else player=PLAYER_A; };
printf("\n\n����ֽ���.\n\n");/*�þ��ѽ���*/
return 0;
};
