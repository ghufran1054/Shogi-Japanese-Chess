#pragma once
#include"Box.h"
#include"utility.h"
class Piece;
class capCell:public Box
{
	vector <Piece*> capPieces;
public:
	
	capCell(int r, int c, int cc, bool isHigh = false);
	void push_Piece(Piece* P);
	void pop_Piece();
	void disp_Cap_Number();
	int size() { return capPieces.size(); }
	Piece* getPiece();
	void highLight();
	void unhighLight();
	void draw();
	void freeMemoryOfPieces();
};

