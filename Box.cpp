#include "Box.h"
#include"utility.h"

void RefreshWindow(RECT*);
void Box::circle_highlight()
{
	
	printImage(h_circle, c*bLen+20, r*bLen+20, c*bLen + bLen-20, r*bLen + bLen-20);
}

void Box::circle_unhighlight()
{
	setcolor(cell_Color);
	setfillstyle(SOLID_FILL, cell_Color);
	fillellipse(c * bLen + bLen / 2, r * bLen + bLen / 2, 16, 15);

}

void Box::box_highlight()
{
	int Color = COLOR(255, 26, 26);
	setcolor(Color);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

	//This Line Draws a thick box one pixel further inside the box. -3  is used with bottom bcz
	//two adjacent boxes already share their boundaries. so addtionl -1 is cause of that one
	rectangle(c * bLen + 3, r * bLen + 3, c * bLen + bLen - 4, r * bLen + bLen - 4);
	setcolor(WHITE);
	RefreshWindow(NULL);
}

void Box::box_unhighlight()
{
	setcolor(cell_Color);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	/*this below statement draws a counter thick rectangle to cover the highlighting of thick box
	*/
	rectangle(c * bLen + 3, r * bLen + 3, c * bLen + bLen - 4, r * bLen + bLen - 4);
	
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	/*then this line draws a black rectangle to restore the orignal thin black boundary*/
	rectangle(c * bLen, r * bLen , c * bLen + bLen - 1 , r * bLen + bLen - 1 );
	setcolor(WHITE);
}

void Box::setColor(int _C)
{
	cell_Color = _C;
}

Box::Box(int _r, int _c, int _cc, bool _isHigh):cell_Color{ _cc }, r{ _r }, c{ _c }, isHigh{ _isHigh }
{
}

void Box::draw()
{
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
	setfillstyle(SOLID_FILL, cell_Color);
	bar3d(c * bLen, r * bLen, c * bLen + bLen, r * bLen + bLen, 0, 0);

}

bool Box::getHighstat()
{
	return isHigh;
}
