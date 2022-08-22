#pragma once
#include"Piece.h"
class Pawn:public Piece
{
protected:
	void prom_image_at(int r, int c);
	void norm_image_at(int r, int c);
public:
	Pawn(int _r, int _c, Color _C, Board* _b, bool _isProm = false);
	bool isLegalMove(int dri, int dci);
	bool isLegalDrop(int dri, int dci);
	void draw();
	virtual int promotion_status(int R);
	char getPieceChar();
};

