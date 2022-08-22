#include "bishop.h"



void bishop::prom_image_at(int r, int c)
{
	/*if (this->C == Color::WHITE)
		readimagefile("Shogi pieces gifs/prombishopW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/prombishopB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (this->C == Color::WHITE)
		printImage(whiteProm[4], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackProm[4], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void bishop::norm_image_at(int r, int c )
{
	/*if (this->C == Color::WHITE)
		readimagefile("Shogi pieces gifs/BishopW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/bishopB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/

	if (this->C == Color::WHITE)
		printImage(whiteNormal[5], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[5], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	
}

bishop::bishop(int _r, int _c, Color _C, Board* B, bool isProm) :Piece(_r, _c, _C, B, isProm)
{
}

bool bishop::isLegalMove(int dri, int dci)
{
	//behaves as king as well as a bishop when promoted
	return (isDiaognal(dri, dci) && isDiognalClear(dri, dci)) || (isPromoted && isLegalKing(dri,dci));
}

void bishop::draw()
{
	if (isPromoted)
	{
		prom_image_at(r, c);
	}
	else
	{
		norm_image_at(r,c);
	}
}

int bishop::promotion_status(int R)
{
	if (can_promote(R))
	{
		return 1;
	}
	return 0;
}

char bishop::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'B';
	}
	else
	{
		return 'b';
	}
}


