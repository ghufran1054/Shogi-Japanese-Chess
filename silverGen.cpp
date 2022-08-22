#include "silverGen.h"


void silverGen::prom_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/promsilvergenW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/promsilvergenB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteProm[3], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackProm[3], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void silverGen::norm_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/silvergenW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/silvergenB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[3], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[3], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

silverGen::silverGen(int _r, int _c, Color _C, Board* B, bool isProm) :Piece(_r, _c, _C, B,isProm)
{
}

bool silverGen::isLegalMove(int dri, int dci)
{
	//behaving as a gold general when promoted
	if (isPromoted)
	{
		return Piece::isLegalGoldGen(dri, dci);
	}

	int Dr = dri - r, Dc = dci - c;
	if (C == Color::WHITE)
	{
		return (abs(Dr) == 1 && isDiaognal(dri, dci)) || (Dr == -1 && Dc == 0);
	}
	else
	{
		return (abs(Dr) == 1 && isDiaognal(dri, dci)) || (Dr == 1 && Dc == 0);
	}
}

void silverGen::draw()
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

int silverGen::promotion_status(int R)
{
	if (can_promote(R))
	{
		return 1;
	}
	return 0;
}

char silverGen::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'S';
	}
	else
	{
		return 's';
	}
}


