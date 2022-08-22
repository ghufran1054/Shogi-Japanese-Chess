#pragma once
#include"Piece.h"
class Lance:public Piece
{
	void prom_image_at(int r, int c);
	void norm_image_at(int r, int c);
public:
	Lance(int _r, int _c, Color _C, Board* B, bool isProm=false);
	bool isLegalMove(int dri, int dci);
	bool isLegalDrop(int dri, int dci);
	void draw();
	virtual int promotion_status(int R);
	char getPieceChar();
};

