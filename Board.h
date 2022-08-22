#pragma once
class Piece;
class Cell;
#include"Player.h"
#include<fstream>
class Board
{
	Cell*** Cs;
public:

	Board(std::ifstream &fin);
	Board();
	Board(const Board& B);
	void displayBoard();
	Piece* getPiece(int r, int c);
	Cell* getCell(int r, int c);
	void move(int sri,int sci,int dri, int dci);
	bool isLegalMove(int sri, int sci, int dri, int dci);
	void highlightCell(int r, int c);
	void findKing(int& r, int& c, int turn);
	bool isLegalDrop(Piece* P,Player*AP, int turn, int dr, int dc);

	//tells if the specified player has made a check on other
	bool isCheck(int turn); 
	bool selfCheck(int sr, int sc, int dr, int dc, int turn);
	bool selfCheckAfterDrop(Piece* sP, int dr, int dc, int turn);
	bool validPieceSelection(Player* AP, int sr, int sc);
	bool validDestSelection(Player* AP, int dr, int dc);
	//tells if specified playe can move or not
	bool isAnyMoveAvailable(Player* AP, int turn); 
	void drawPiece(int r, int c);

	void freeBoardPieces();
	void loadBoardPieces(std::ifstream& fin);
	~Board();
};

