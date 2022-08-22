#include "Lance.h"

void Lance::prom_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/promlanceW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/promlanceB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteProm[1], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackProm[1], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void Lance::norm_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/lanceW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/lanceB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[1], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[1], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

Lance::Lance(int _r, int _c, Color _C, Board* B, bool isProm):Piece(_r,_c,_C,B,isProm)
{
}

bool Lance::isLegalMove(int dri, int dci)
{
	int Dr = dri - r;
	//behaving as a gold general when promoted
	if (isPromoted)
	{
		return Piece::isLegalGoldGen(dri, dci);
	}

	if (C == Color::WHITE)
	{
		return (Dr < 0 && isVertical(dri, dci) && isVerticalClear(dri, dci));
	}
	else
	{
		return (Dr > 0 && isVertical(dri, dci) && isVerticalClear(dri, dci));
	}
}

bool Lance::isLegalDrop(int dri, int dci)
{
	int nARow = (C == Color::WHITE ? 0 : 8);
	return Piece::isLegalDrop(dri, dci) && (dri != nARow);
}

void Lance::draw()
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

int Lance::promotion_status(int R)
{
	if (can_promote(R))
	{
		if (C == Color::WHITE)
		{
			if (R == 0)
			{
				return 2;
			}
		}
		else
		{
			if (R == 8)
			{
				return 2;
			}
		}
		return 1;
	}
	return 0;
}

char Lance::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'L';
	}
	else
	{
		return 'l';
	}
}
