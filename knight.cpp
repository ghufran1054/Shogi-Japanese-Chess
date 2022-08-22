#include "knight.h"

void knight::prom_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/promknightW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/promknightB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteProm[5], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackProm[5], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void knight::norm_image_at(int r, int c)
{
	//if (C == Color::WHITE)
	//	readimagefile("Shogi pieces gifs/KnightW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	//else
	//	readimagefile("Shogi pieces gifs/KnightB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	if (C == Color::WHITE)
		printImage(whiteNormal[6], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[6], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

knight::knight(int _r, int _c, Color _C, Board* B, bool isProm) :Piece(_r, _c, _C, B, isProm)
{
}

bool knight::isLegalMove(int dri, int dci)
{
	//behaving as a gold general when promoted
	if (isPromoted)
	{
		return Piece::isLegalGoldGen(dri, dci);
	}

	int Dr = dri - r, Dc =abs(dci - c);
	if (C == Color::WHITE)
	{
		return Dr == -2 && Dc == 1;
	}
	else
	{
		return Dr == 2 && Dc == 1;
	}
}

bool knight::isLegalDrop(int dri, int dci)
{
	int mARow = (C == Color::WHITE ? 8 : 6);
	int lARow = (C == Color::WHITE ? 2 : 0);
	return Piece::isLegalDrop(dri, dci) && (dri >= lARow && dri <= mARow);
}

void knight::draw()
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

int knight::promotion_status(int R)
{
	if (can_promote(R))
	{
		if (C == Color::WHITE)
		{
			if (R == 0 || R == 1)
			{
				return 2;
			}
			
		}
		else //Black knight
		{
			if (R == 7 || R == 8)
			{
				return 2;
			}
		}
		return 1;
		
	}
	return 0;
}

char knight::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'N';
	}
	else
	{
		return 'n';
	}
}




