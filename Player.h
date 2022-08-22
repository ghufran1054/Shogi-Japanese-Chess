#pragma once
#include<string>
#include"utility.h"
#include<fstream>
#include"Timer.h"
class Piece;
class capCell;
class Board;
class Player
{
	string name;
	Color C;
	Timer T;
	


	////functions related to capturedPieces
	//capCell* capturedPieces[7];

	//void freeMemoryOfPieces_Of(int type);
	//void push_backPiece(Piece* P);
	//void pop_backPiece(int type);
	//void disp_All_Captured();
	//int getPieceCountOf(int type);
	//void disp_Captured(int type);
	//void disp_All_Cap_Count();
	//void disp_Cap_Count_Of(int type);
	//bool isPiece_Present(int type);//tells if the piece of given type exists
	//void highlight_Cell(int type);
	//void update_Cell_Info(int type);
	//Piece* extractPiece(int type);
	//void unhighlight_Cell(int type);
public:
	Player(const string& n, Color _C, Timer _T ={-1,-1});
	Timer getTime();
	void setTime(const Timer& T);
	void setName(const string& N);
	void displayTime();
	void decrementTime();

	string getName();
	Color getColor();
	~Player();
};

