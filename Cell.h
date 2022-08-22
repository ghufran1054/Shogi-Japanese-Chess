#pragma once
class Piece;
#include"Box.h"
class Cell:public Box
{
protected:
	Piece* P;

public:
	Cell(Piece* _p, int _r, int _c, int _cc, bool _isHigh=false);
	Cell(const Cell& C);
	Piece* getPiece();
	void setPiece(Piece* _p);
	void highLight();
	void unhighLight();

	void draw();
	~Cell();
};

