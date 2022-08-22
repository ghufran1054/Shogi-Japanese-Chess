#include "rook.h"


void rook::prom_image_at(int r, int c)
{
	if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/promrookW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/promrookB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void rook::norm_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/rookW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/rookB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[2], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[2], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

rook::rook(int _r, int _c, Color _C, Board* B, bool isProm) :Piece(_r, _c, _C, B, isProm)
{
}

bool rook::isLegalMove(int dri, int dci)
{
	return (isHorizontal(dri, dci) && isHorizonClear(dri, dci) || isVertical(dri, dci) && isVerticalClear(dri, dci) || (isPromoted && isLegalKing(dri,dci)));
}

void rook::draw()
{
	
	if (isPromoted)
	{
		prom_image_at(r, c);
	}
	else
	{
		norm_image_at(r, c);
	}

}

int rook::promotion_status(int R)
{
	if (can_promote(R))
	{
		return 1;
	}
	return 0;
}

char rook::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'R';
	}
	else
	{
		return 'r';
	}
}

