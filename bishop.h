#pragma once
#include"Piece.h"
class bishop:public Piece
{
protected:
	void prom_image_at(int r, int c);
	void norm_image_at(int r, int c);
public:
	bishop(int _r, int _c, Color _C, Board* B, bool isProm = false);
	bool isLegalMove(int dri, int dci);
	void draw();
	virtual int promotion_status(int R);
	char getPieceChar();
};

