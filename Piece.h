#pragma once
#include"utility.h"

class Board;
class Piece
{
protected:
	int r, c;
	Color C;
	Board* B;
	bool isPromoted;
	bool isHorizontal(int dri, int dci);
	bool isVertical(int dri, int dci);
	bool isDiaognal(int dri, int dci);
	bool isHorizonClear(int dri, int dci);
	bool isVerticalClear(int dri, int dci);
	bool isDiognalClear(int dri, int dci);
	bool isLegalGoldGen(int dri, int dci);
	bool isLegalKing(int dri, int dci);
	bool can_promote(int R);
public:
	void virtual prom_image_at(int r, int c) = 0;
	void virtual norm_image_at(int r, int c) = 0;
	char virtual getPieceChar() = 0;
	void promote(bool yes);
	Piece(int _r, int _c, Color _C, Board* _b, bool isProm = false);
	virtual void draw() = 0;
	virtual bool isLegalMove(int dri, int dci) = 0;
	virtual bool isLegalDrop(int dri, int dci);
	void move(int _r, int _c);
	void setBoard(Board* _B);
	void setColor(Color _C);
	virtual int promotion_status(int R)=0;
	bool isPiecePromoted() { return isPromoted; }
	Color getColor();
};

