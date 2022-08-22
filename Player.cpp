#include "Player.h"
#include"Piece.h"
#include"capCells.h"
/* these are for the pieces to be stored in capcells array
0 for pawn
1 for lance
2 for rook
3 for silverGen
4 for goldGen
5 for bishop
6 for knight
*/

int getPieceType(Piece* P);


Player::Player(const string& n, Color _C,Timer _T):name{n},C{_C},T{_T}
{
	
}

Timer Player::getTime()
{
	return T;
}

void Player::setTime(const Timer& T)
{
	this->T = T;
}

void Player::setName(const string& N)
{
	this->name = N;
}

void Player::displayTime()
{
	if (T == Timer{ -1,-1 })
		return;
	int oldColor = getcolor(), oldbkColor = getbkcolor();
	
	bgiout << T;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
	setbkcolor(BLACK);
	setcolor(WHITE);

	if (C == Color::WHITE)
	{
		outstreamxy(13 * bLen - 18, 6 * bLen - 28);
	}
	else
	{	
		outstreamxy(13 * bLen - 18, 2 * bLen - 18);
	}
	setcolor(oldColor);
	setbkcolor(oldbkColor);

}

//void Player::freeMemoryOfPieces_Of(int type)
//{
//	capturedPieces[type]->freeMemoryOfPieces();
//}

void Player::decrementTime()
{
	--this->T;
}





//void Player::disp_Cap_Count_Of(int type)
//{
//	capturedPieces[type]->disp_Cap_Number();
//}
//
//bool Player::isPiece_Present(int type)
//{
//	return (capturedPieces[type]->size() != 0);
//}

//void Player::highlight_Cell(int type)
//{
//	capturedPieces[type]->highLight();
//}
//
//void Player::update_Cell_Info(int type)
//{
//	capturedPieces[type]->draw();
//	capturedPieces[type]->disp_Cap_Number();
//}

//Piece* Player::extractPiece(int type)
//{
//	Piece* P = capturedPieces[type]->getPiece();
//	return P;
//}
//
//void Player::unhighlight_Cell(int type)
//{
//	capturedPieces[type]->unhighLight();
//}

string Player::getName()
{
	return name;
}

Color Player::getColor()
{
	return C;
}

Player::~Player()
{
	/*for (int i = 0; i < 7; i++)
		delete capturedPieces[i];*/
}
