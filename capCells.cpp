#include "capCells.h"
#include"Piece.h"
#include<iomanip>
capCell::capCell(int r, int c, int cc, bool isHigh):Box{r,c,cc,isHigh}, capPieces(0)
{
}

void capCell::push_Piece(Piece* P)
{
	capPieces.push_back(P);
}

void capCell::pop_Piece()
{
	capPieces.pop_back();
}

void capCell::disp_Cap_Number()
{
	setcolor(GOLD_COLOR);//gold color
	setfillstyle(SOLID_FILL, GOLD_COLOR);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	setbkcolor(BLACK);
	bgiout << capPieces.size();

	printImage(gBox, c * bLen + bLen / 2 - 15, r * bLen - 35, c * bLen + bLen / 2 + 15, r * bLen - 5);
	if (capPieces.size() > 9)
	{
		outstreamxy(c  * bLen + bLen / 2 - 10, r * bLen - 20 - 8);
	}
	else
	{
		outstreamxy(c * bLen + bLen / 2 - 6, r * bLen - 20 - 8);
	}
	setcolor(WHITE);
	setbkcolor(BLACK);
}

Piece* capCell::getPiece()
{
	return capPieces[capPieces.size() - 1];
}

void capCell::highLight()
{
	box_highlight();

}

void capCell::unhighLight()
{
	box_unhighlight();
}



void capCell::draw()
{
	Box::draw();
	if (capPieces.size() != 0)
	{
		capPieces[0]->draw();
	}
	setcolor(WHITE);
}

void capCell::freeMemoryOfPieces()
{
	for (int i = 0; i < capPieces.size(); i++)
	{
		delete capPieces[i];
	}
	capPieces = {};
}
