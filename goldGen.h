#pragma once
#include"Piece.h"
class goldGen:public Piece
{
protected:
	void prom_image_at(int r, int c);
	void norm_image_at(int r, int c);
public:
	goldGen(int _r, int _c, Color _C, Board* B, bool isProm = false);
	bool isLegalMove(int dri, int dci);
	void draw();
	virtual int promotion_status(int R) { return 0; }
	char getPieceChar();
};

