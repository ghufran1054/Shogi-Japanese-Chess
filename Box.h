#pragma once
class Box
{
protected:
	int cell_Color, r, c;
	bool isHigh;
	void circle_highlight();
	void circle_unhighlight();
	void box_highlight();
	void box_unhighlight();

public:
	void setColor(int _C);
	int getColor() { return cell_Color; }
	Box(int _r, int _c, int _cc, bool _isHigh = false);
	void draw();
	bool getHighstat();

};

