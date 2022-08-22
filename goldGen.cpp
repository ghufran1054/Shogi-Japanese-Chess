#include "goldGen.h"


void goldGen::prom_image_at(int r, int c)
{
	
}

void goldGen::norm_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/goldgeneralW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/goldgeneralB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[4], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[4], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

goldGen::goldGen(int _r, int _c, Color _C, Board* B,bool isProm) :Piece(_r, _c, _C, B,isProm)
{
}

bool goldGen::isLegalMove(int dri, int dci)
{
	return Piece::isLegalGoldGen(dri, dci);
}

void goldGen::draw()
{
	norm_image_at(r, c);
}

char goldGen::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'G';
	}
	else
	{
		return 'g';
	}
}



