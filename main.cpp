#include <iostream>
#include <time.h>
#include <random>
#include <unistd.h>

using namespace std;

const int boardx =10, boardy=15;
int curPiece =0;
bool piecePos[boardy][boardx];
bool lost =false;

bool board[boardy][boardx] = {
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					};

//function declerations
void gameOver();
bool checkOverLap(int y,int x);
void addAndCheck(int y,int x);
void spawnPiece();
void printBoard();
void frameRule();
void frame();
bool canMoveDown();
void movePieceDown();
void updateBoard();
void lockPiece();
//---------------------


int main(void)
{
	srand (time(NULL));
	spawnPiece();
	while(!lost)
    {
		frameRule();
	}
	cout<<"GAME OVER"<<endl;
}

void printBoard(){
	
	for(int i=0;i<boardy;i++)
	{
		cout<<"|";
		
		for(int j=0;j<boardx;j++)
		{
			if(board[i][j] || piecePos[i][j])
			{
				cout<<'#';
			}
			else
			{
				cout<<' ';
			}
		}
		
		cout<<"|"<<endl;
	}
	cout<<"|----------|"<<endl;
}

void spawnPiece(){
	int p = rand() % 7;
	
	if(p==0)//long
	{
		addAndCheck(0,3);
		addAndCheck(0,4);
		addAndCheck(0,5);
		addAndCheck(0,6);
		curPiece =0;
	}
	else if(p==1)//Backwards L
	{
		addAndCheck(0,3);
		addAndCheck(1,3);
		addAndCheck(1,4);
		addAndCheck(1,5);
		curPiece =1;
	}
	else if(p==2)//L
	{
		addAndCheck(0,5);
		addAndCheck(1,3);
		addAndCheck(1,4);
		addAndCheck(1,5);
		curPiece =2;
	}
	else if(p==3)//box
	{
		addAndCheck(0,4);
		addAndCheck(0,5);
		addAndCheck(1,4);
		addAndCheck(1,5);
		curPiece =3;
	}
	else if(p==4)//Backwards Z
	{
		addAndCheck(0,4);
		addAndCheck(0,5);
		addAndCheck(1,3);
		addAndCheck(1,4);
		curPiece =4;
	}
	else if(p==5)//Z
	{
		addAndCheck(0,3);
		addAndCheck(0,4);
		addAndCheck(1,4);
		addAndCheck(1,5);
		curPiece =5;
	}
	else//nub
	{
		addAndCheck(0,4);
		addAndCheck(1,3);
		addAndCheck(1,4);
		addAndCheck(1,5);
		curPiece =6;
	}	
	return;
}

//I am very proud of this function
bool canMoveDown(){
	
	int lowestInX[boardx]={0,0,0,0,0,0,0,0,0,0};
	
		for(int i=0;i<boardy;i++)
		{		
			for(int j=0;j<boardx;j++)
			{
				if(piecePos[i][j])
				{
					lowestInX[j]=i;
				}
			}
			
		}
	
	for(int i=0;i<boardx;i++)
	{
		if(board[(lowestInX[i])+1][i] || lowestInX[i] == 14)
		{
			//cout<<"cannot move down"<<endl;
			return false;
		}
	}
	
	//cout<<"can move down"<<endl;
	return true;
}

void addAndCheck(int y,int x){
	if(checkOverLap(y,x))
	{
		gameOver();
	}
	else
	{
		piecePos[y][x] =true;
	}
}

//returns true if overlap
bool checkOverLap(int y,int x){
	return board[y][x];
}

void gameOver(){
	lost=true;
}

void clearScreen(){
	cout << "\033[2J\033[1;1H";
}

void frameRule(){
	
	for(int i=0;i<30;i++)
	{
		frame();
		usleep(33333);
		clearScreen();
	}
	updateBoard();
}

void frame()
{
	printBoard();
}

void updateBoard()
{
	if(canMoveDown())
	{
		movePieceDown();
	}
	else
	{
		lockPiece();
	}
}

void movePieceDown()
{
	bool oldPiecePos[boardy][boardx];
	
	for(int i=0;i<boardy;i++)
	{
		for(int j=0;j<boardx;j++)
		{
				oldPiecePos[i][j] = piecePos[i][j];
				piecePos[i][j]=false;
		}
	}
	for(int i=0;i<boardy;i++)
	{
		for(int j=0;j<boardx;j++)
		{
			if(oldPiecePos[i][j])
			{
				piecePos[i+1][j]= true;
			}
		}
	}
}

void lockPiece()
{
	for(int i=0;i<boardy;i++)
	{
		for(int j=0;j<boardx;j++)
		{
			if(piecePos[i][j])
			{
				board[i][j]=true;
			}
			piecePos[i][j]=false;
		}
	}
	spawnPiece();
}

