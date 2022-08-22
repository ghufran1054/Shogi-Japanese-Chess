#include "Piece.h"
#include"Board.h"

void Piece::setColor(Color _C)
{
	C = _C;
}
bool Piece::can_promote(int R)
{
	if (C == Color::WHITE)
	{
		return R <= 2 && R >= 0;
	}
	else
	{
		return R >= 6 && R <= 8;
	}
}
bool Piece::isHorizontal(int dri, int dci)
{
	return r == dri;
}

bool Piece::isVertical(int dri, int dci)
{
	return c == dci;
}

bool Piece::isDiaognal(int dri, int dci)
{
	return abs(r - dri) == abs(c - dci);
}

bool Piece::isHorizonClear(int dri, int dci)
{
	int start, end;
	if (dci > c)
	{
		start = c + 1;
		end = dci - 1;
	}
	else
	{
		start = dci + 1;
		end = c - 1;
	}
	for (int ci = start; ci <= end; ci++)
	{
		if (B->getPiece(r,ci) != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Piece::isVerticalClear(int dri, int dci)
{
	int start, end;
	if (dri > r)
	{
		start = r + 1;
		end = dri - 1;
	}
	else
	{
		start = dri + 1;
		end = r - 1;
	}
	for (int ri=start; ri <= end; ri++)
	{
		if (B->getPiece(ri, c) != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Piece::isDiognalClear(int dri, int dci)
{
	int lim = abs(dri - r);
	if (dri < r && dci > c)
	{
		for (int i = 1; i < lim; i++)
		{
			if (B->getPiece(r - i, c + i) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dri < r && dci < c)
	{
		for (int i = 1; i < lim; i++)
		{
			if (B->getPiece(r - i, c - i) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dri > r && dci < c)
	{
		for (int i = 1; i < lim; i++)
		{
			if (B->getPiece(r + i, c - i) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dri > r && dci > c)
	{
		for (int i = 1; i < lim; i++)
		{
			if (B->getPiece(r + i, c + i) != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

bool Piece::isLegalGoldGen(int dri, int dci)
{
	int Dr = dri - r, Dc = dci - c;
	if (C == Color::WHITE)
	{
		return (Dr == -1 && isDiaognal(dri, dci)) || (abs(Dc) == 1 && isHorizontal(dri, dci)) || (abs(Dr) == 1 && isVertical(dri, dci));
	}
	else
	{
		return (Dr == 1 && isDiaognal(dri, dci)) || (abs(Dc) == 1 && isHorizontal(dri, dci)) || (abs(Dr) == 1 && isVertical(dri, dci));
	}
}

bool Piece::isLegalKing(int dri, int dci)
{
	int Dr = abs(r - dri), Dc = abs(dci - c);
	return (Dr == 0 || Dr == 1) && (Dc == 0 || Dc == 1);
}

void Piece::promote(bool yes)
{
	if (yes)
	{
		isPromoted = true;
	}
	else
	{
		isPromoted = false;
	}
}

Piece::Piece(int _r, int _c, Color _C,Board* _b, bool isProm):r{_r},c{_c},C{_C},B{_b}, isPromoted{ isProm }
{
}

bool Piece::isLegalDrop(int dri, int dci)
{
	return B->getPiece(dri, dci) == nullptr;
}

void Piece::move(int _r, int _c)
{
	this->r = _r, this->c = _c;
}

void Piece::setBoard(Board* _B)
{
	B = _B;
}

Color Piece::getColor()
{
	return C;
}
