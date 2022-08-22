#include "Cell.h"
#include"utility.h"
#include"Piece.h"
#include"Pawn.h"
#include"rook.h"
#include"king.h"
#include"knight.h"
#include"silverGen.h"
#include"goldGen.h"
#include"Bishop.h"
#include"lance.h"






Cell::Cell(Piece* _p, int _r, int _c, int _cc, bool _isHigh):P{_p}, Box(_r,_c,_cc,isHigh)
{
}

Cell::Cell(const Cell& C):Box(C.r,C.c,C.cell_Color,C.isHigh)
{
	
	if (C.P == nullptr)
	{
		P = nullptr;
	}
	else
	{

		Pawn* Cp = dynamic_cast<Pawn*>(C.P);
		if (Cp != nullptr)
		{
			P = new Pawn(*Cp);
			return;
		}
		Lance* Lp = dynamic_cast<Lance*>(C.P);
		if (Lp != nullptr)
		{
			P = new Lance(*Lp);
			return;
		}
		rook* Rp = dynamic_cast<rook*>(C.P);
		if (Rp != nullptr)
		{
			P = new rook(*Rp);
			return;
		}
		King* Kp = dynamic_cast<King*>(C.P);
		if (Kp != nullptr)
		{
			P = new King(*Kp);
			return;
		}
		silverGen* Sp = dynamic_cast<silverGen*>(C.P);
		if (Sp != nullptr)
		{
			P = new silverGen(*Sp);
			return;
		}
		goldGen* Gp = dynamic_cast<goldGen*>(C.P);
		if (Gp != nullptr)
		{
			P = new goldGen(*Gp);
			return;
		}
		bishop* Bp = dynamic_cast<bishop*>(C.P);
		if (Bp != nullptr)
		{
			P = new bishop(*Bp);
			return;
		}
		knight* Knp = dynamic_cast<knight*>(C.P);
		P = new knight(*Knp);
	}
}

Piece* Cell::getPiece()
{
	return P;
}



void Cell::setPiece(Piece* _p)
{
	P = _p;
}

void Cell::draw()
{
	Box::draw();
	if (P != nullptr)
		P->draw();
	setcolor(WHITE);
}

Cell::~Cell()
{
	delete P;
}

void Cell::highLight()
{
	this->isHigh = true;

	if (P != nullptr)
	{
		box_highlight();
	}
	else
	{
		circle_highlight();
	}

}



void Cell::unhighLight()
{
	this->isHigh = false;

	if (P != nullptr)
	{
		box_unhighlight();
	}
	else 
	{
		circle_unhighlight();
	}

}
