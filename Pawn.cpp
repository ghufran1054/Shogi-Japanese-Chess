#include "Pawn.h"
#include"utility.h"
#include"Board.h"

void Pawn::prom_image_at(int r, int c)
{
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/PromPawnW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/promPawnB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteProm[0], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackProm[0], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

void Pawn::norm_image_at(int r, int c)
{
	
	/*if (C == Color::WHITE)
		readimagefile("Shogi pieces gifs/PawnW.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		readimagefile("Shogi pieces gifs/pawnB.gif", c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);*/
	if (C == Color::WHITE)
		printImage(whiteNormal[0], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
	else
		printImage(blackNormal[0], c * bLen + iStart, r * bLen + iStart, c * bLen + iEnd, r * bLen + iEnd);
}

Pawn::Pawn(int _r, int _c, Color _C, Board* _b, bool _isProm) :Piece(_r, _c, _C, _b,_isProm)
{

}
bool Pawn::isLegalMove(int dri, int dci)
{
	//behaving as a gold general when promoted
	if (isPromoted)
	{
		return Piece::isLegalGoldGen(dri, dci);
	}

	int Dr = dri - r, Dc = dci - c;
	if (C == Color::WHITE)
	{
		return Dr == -1 && Dc == 0;
	}
	else
	{
		return Dr == 1 && Dc == 0;
	}
}
bool Pawn::isLegalDrop(int dri, int dci)
{
	int nARow = (C == Color::WHITE ? 0 : 8);
	for (int r = 0; r < 9; r++)
	{
		Pawn* P = dynamic_cast<Pawn*>(B->getPiece(r, dci));
		if (P != nullptr && P->getColor() == C && P->isPromoted == false)
		{
			return false;
		}
	}
	return Piece::isLegalDrop(dri, dci) && (dri != nARow);
	
}
void Pawn::draw()
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

int Pawn::promotion_status(int R)
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

char Pawn::getPieceChar()
{
	if (C == Color::WHITE)
	{
		return 'P';
	}
	else
	{
		return 'p';
	}
}
