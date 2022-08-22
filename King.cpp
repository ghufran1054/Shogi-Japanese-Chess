#include "King.h"
void King::prom_image_at(int r, int c)
{
}
void King::norm_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/KingW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/KingB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[7], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[7], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}
King::King(int _r, int _c, Color _C, Board* B, bool isProm) :Piece(_r, _c, _C, B, isProm)
{
}

bool King::isLegalMove(int dri, int dci)
{
	return Piece::isLegalKing(dri, dci);
}

void King::draw()
{
	norm_image_at(r, c);
}

char King::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'K';
	}
	else
	{
		return 'k';
	}
}
