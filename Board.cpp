#include "Board.h"
#include"Pawn.h"
#include"Lance.h"
#include"King.h"
#include"bishop.h"
#include"rook.h"
#include"goldGen.h"
#include"silverGen.h"
#include"knight.h"
#include"Cell.h"
Board::Board(std::ifstream &fin)
{
	Cs = new Cell * *[9];
	int color{};
	Color pieceColor{};
	char pieceChar{};
	bool prom{};
	string input;
	for (int r = 0; r < 9; r++)
	{
		Cs[r] = new Cell * [9];
		for (int c = 0; c < 9; c++)
		{
			if ((r + c) % 2 == 0)

				color = COLOR(255, 223, 128);
			else
				color = COLOR(179, 134, 0);

			fin >> input;
			pieceChar=input[0];

			if (input.size() == 2)
			{
				prom = true;
			}
			else
			{
				prom = false;
			}
			if (islower(pieceChar))
			{
				pieceColor = Color::BLACK;
			}
			else
			{
				pieceColor = Color::WHITE;
			}
			if (tolower(pieceChar) == 'p')
			{
				Cs[r][c] = new Cell(new Pawn(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'l')
			{
				Cs[r][c] = new Cell(new Lance(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'k')
			{
				Cs[r][c] = new Cell(new King(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'r')
			{
				Cs[r][c] = new Cell(new  rook(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'b')
			{
				Cs[r][c] = new Cell(new bishop(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'g')
			{
				Cs[r][c] = new Cell(new goldGen(r, c, pieceColor, this, prom), r, c, color);
			}
		
			else if (tolower(pieceChar) == 's')
			{
				Cs[r][c] = new Cell(new silverGen(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else if (tolower(pieceChar) == 'n')
			{
				Cs[r][c] = new Cell(new knight(r, c, pieceColor, this, prom), r, c, color);
			}
			
			else
				Cs[r][c] = new Cell(nullptr, r, c, color);
		}

	}
	
}
Board::Board()
{
	Cs = new Cell * *[9];
	int color;
	for (int r = 0; r < 9; r++)
	{
		Cs[r] = new Cell * [9];
		for (int c = 0; c < 9; c++)
		{
			if ((r + c) % 2 == 0)
				
				color = COLOR(255, 223, 128);
			else
				color = COLOR(179, 134, 0);
			if (r == 2)
			{
				Cs[r][c] = new Cell(new Pawn(r, c, Color::BLACK, this), r, c, color);
			}
			else if (r == 6)
			{
				Cs[r][c] = new Cell(new Pawn(r, c, Color::WHITE, this), r, c, color);
			}
			else if (r == 0 && c == 0 || r == 0 && c == 8)
			{
				Cs[r][c] = new Cell(new Lance(r, c, Color::BLACK, this), r, c, color);
			}
			else if (r == 8 && c == 0 || r == 8 && c == 8)
			{
				Cs[r][c] = new Cell(new Lance(r, c, Color::WHITE, this), r, c, color);
			}
			else if (r == 0 && c == 4)
			{
				Cs[r][c] = new Cell(new King(r, c, Color::BLACK, this), r, c, color);
			}
			else if (r == 8 && c == 4)
			{
				Cs[r][c] = new Cell(new King(r, c, Color::WHITE, this), r, c, color);
			}
			else if (r == 1 && c == 1)
			{
				Cs[r][c] = new Cell(new  rook(r, c, Color::BLACK, this), r, c, color);
			}
			else if (r == 7 && c == 7)
			{
				Cs[r][c] = new Cell(new rook(r, c, Color::WHITE, this), r, c, color);
			}															 
			else if (r == 1 && c == 7)
			{
				Cs[r][c] = new Cell(new bishop(r , c , Color::BLACK, this), r , c, color);
			}
			else if (r == 7 && c == 1)
			{
				Cs[r][c] = new Cell(new bishop(r, c, Color::WHITE, this), r, c, color);
			}
			else if ((c == 3 || c == 5) && r == 0)
			{
				Cs[r][c] = new Cell(new goldGen(r, c, Color::BLACK, this), r, c, color);
			}
			else if ((c == 3 || c == 5) && r == 8)
			{
				Cs[r][c] = new Cell(new goldGen(r, c, Color::WHITE, this), r, c, color);

			}
			else if ((c == 2 || c == 6) && r == 0)
			{
				Cs[r][c] = new Cell(new silverGen(r, c, Color::BLACK, this), r, c, color);
			}
			else if ((c == 2 || c == 6) && r == 8)
			{
				Cs[r][c] = new Cell(new silverGen(r, c, Color::WHITE, this), r, c, color);
			}
			else if (r == 0 && (c == 1 || c == 7))
			{
				Cs[r][c] = new Cell(new knight(r, c, Color::BLACK, this), r, c, color);
			}
			else if (r == 8 && (c == 1 || c == 7))
			{
				Cs[r][c] = new Cell(new knight(r, c, Color::WHITE, this), r, c, color);
			}
			else
				Cs[r][c] = new Cell(nullptr, r, c, color);
		}

	}

}

Board::Board(const Board& B)
{
	this->Cs = new Cell * *[9];
	for (int r = 0; r < 9; r++)
	{
		Cs[r] = new Cell * [9];
		for (int c = 0; c < 9; c++)
		{
			Cs[r][c] = new Cell(*B.Cs[r][c]);
			//Setting the this board as the board for the new pieces
			if (Cs[r][c]->getPiece() != nullptr)
			{
				Cs[r][c]->getPiece()->setBoard(this);
			}
		}
	}
}

void Board::displayBoard()
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			Cs[r][c]->draw();
		}
	}
}

Piece* Board::getPiece(int r, int c)
{
	return Cs[r][c]->getPiece();
}

Cell* Board::getCell(int r, int c)
{
	return Cs[r][c];
}

void Board::move(int sri, int sci, int dri, int dci)
{
	Cs[dri][dci]->setPiece(Cs[sri][sci]->getPiece());
	Cs[sri][sci]->setPiece(nullptr);
	Cs[dri][dci]->getPiece()->move(dri, dci);
}

bool Board::isLegalMove(int sri, int sci, int dri, int dci)
{
	return Cs[sri][sci]->getPiece()->isLegalMove(dri, dci);
}


void Board::highlightCell(int r, int c)
{
	Cs[r][c]->highLight();
}

void Board::findKing(int& r, int& c, int turn)
{
	Color C = (turn == 1 ? Color::WHITE : Color::BLACK);
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			King* Kp = dynamic_cast<King*>(Cs[ri][ci]->getPiece());
			if (Kp != nullptr && Kp->getColor() == C)
			{
				r = ri, c = ci;
				return;
			}
		}
	}
}

//it recieves a turn and the player opposite to that turn. e.g Black Player and turn 1(White)
bool Board::isLegalDrop(Piece* P, Player*AP, int turn,int dr, int dc)
{
	//white player and black turn recieved
	bool condition = true;
	Pawn* Pp = dynamic_cast<Pawn*>(P);
	if (Pp != nullptr) //If its a Pawn
	{
		Board tempB(*this);
		P->move(dr, dc);
		tempB.getCell(dr, dc)->setPiece(P);

		//e.g White ne check mardye likin Black cannot move. not allowed for pawns to checkmate with a drop
		if (!tempB.isAnyMoveAvailable(AP, !turn) && tempB.isCheck(turn))
		{
			condition = false;
		}
		tempB.getCell(dr, dc)->setPiece(nullptr);
		P->move((turn == 0 ? bcpRow : wcpRow), cpCol);
	}
	return condition && P->isLegalDrop(dr,dc);
}

bool Board::isCheck(int turn)
{
	turn = (turn + 1) % 2;
	int kr, kc;
	findKing(kr, kc, turn);
	turn = (turn + 1) % 2;
	Color C = (turn == 1 ? Color::WHITE : Color::BLACK);
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			Piece* P = getPiece(ri, ci);
			if (P !=nullptr && P->getColor()==C && isLegalMove(ri, ci, kr, kc))
			{
				return true;
			}
		}
	}
	return false;
}

bool Board::selfCheck(int sr, int sc, int dr, int dc, int turn)
{/*
	Board tempB(*this);
	if(!(sr==dr && sc==dc))
		tempB.move(sr, sc, dr, dc);
	return tempB.isCheck((turn + 1) % 2);*/

	//saving the piece at destination
	Piece* P = this->getPiece(dr, dc);

	//moving the pieces
	this->getCell(dr,dc)->setPiece(this->getPiece(sr, sc));
	this->getCell(sr, sc)->setPiece(nullptr);

	//checking check
	bool con = (isCheck(!turn));

	//reverting the move
	this->getCell(sr, sc)->setPiece(this->getPiece(dr, dc));
	this->getCell(dr, dc)->setPiece(P);

	return con;
}

bool Board::selfCheckAfterDrop(Piece*sP, int dr, int dc, int turn)
{
	Board tempB(*this);
	tempB.getCell(dr, dc)->setPiece(sP);
	bool toReturn = tempB.isCheck((turn + 1) % 2);
	tempB.getCell(dr, dc)->setPiece(nullptr);
	return toReturn;
}

bool Board::validPieceSelection(Player* AP, int sr, int sc)
{
	if (sr < 0 || sr>8 || sc < 0 || sc>8)
		return false;

	Piece* P = getPiece(sr, sc);
	return P != nullptr && P->getColor() == AP->getColor();
}

bool Board::validDestSelection(Player* AP, int dr, int dc)
{
	if (dr < 0 || dr>8 || dc < 0 || dc>8)
		return false;

	Piece* P = getPiece(dr, dc);
	return P == nullptr || P->getColor() != AP->getColor();
}

bool Board::isAnyMoveAvailable(Player* AP, int turn)
{
	for (int sr = 0; sr < 9; sr++)
	{
		for (int sc = 0; sc < 9; sc++)
		{
			for (int dr = 0; dr < 9; dr++)
			{
				for (int dc = 0; dc < 9; dc++)
				{
					if (validPieceSelection(AP, sr, sc) && isLegalMove(sr, sc, dr, dc) && validDestSelection(AP, dr, dc) && !selfCheck(sr, sc, dr, dc, turn))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Board::drawPiece(int r, int c)
{
	Cs[r][c]->draw();
}

void Board::freeBoardPieces()
{
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			delete Cs[ri][ci]->getPiece();
			Cs[ri][ci]->setPiece(nullptr);
		}
	}
}

void Board::loadBoardPieces(std::ifstream& fin)
{
	int color{};
	char pieceChar{};
	bool prom{};
	Color pieceColor{};
	string input;
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			

			
			/*fin >> input;
			pieceChar = input[0];
			
			if (pieceChar == 'p')
			{
				Cs[r][c]->setPiece(new Pawn(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'P')
			{
				Cs[r][c]->setPiece(new Pawn(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'l')
			{
				Cs[r][c]->setPiece(new Lance(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'L')
			{
				Cs[r][c]->setPiece(new Lance(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'k')
			{
				Cs[r][c]->setPiece(new King(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'K')
			{
				Cs[r][c]->setPiece(new King(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'r')
			{
				Cs[r][c]->setPiece(new  rook(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'R')
			{
				Cs[r][c]->setPiece(new rook(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'b')
			{
				Cs[r][c]->setPiece(new bishop(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'B')
			{
				Cs[r][c]->setPiece(new bishop(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'g')
			{
				Cs[r][c]->setPiece(new goldGen(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'G')
			{
				Cs[r][c]->setPiece(new goldGen(r, c, Color::WHITE, this, prom));

			}
			else if (pieceChar == 's')
			{
				Cs[r][c]->setPiece(new silverGen(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'S')
			{
				Cs[r][c]->setPiece(new silverGen(r, c, Color::WHITE, this, prom));
			}
			else if (pieceChar == 'n')
			{
				Cs[r][c]->setPiece(new knight(r, c, Color::BLACK, this, prom));
			}
			else if (pieceChar == 'N')
			{
				Cs[r][c]->setPiece(new knight(r, c, Color::WHITE, this, prom));
			}
			else
				Cs[r][c]->setPiece(nullptr);*/

			fin >> input;
			pieceChar = input[0];

			if (input.size() == 2)
			{
				prom = true;
			}
			else
			{
				prom = false;
			}
			if (islower(pieceChar))
			{
				pieceColor = Color::BLACK;
			}
			else
			{
				pieceColor = Color::WHITE;
			}
			if (tolower(pieceChar) == 'p')
			{
				Cs[r][c]->setPiece(new Pawn(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'l')
			{
				Cs[r][c]->setPiece(new Lance(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'k')
			{
				Cs[r][c]->setPiece(new King(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'r')
			{
				Cs[r][c]->setPiece(new  rook(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'b')
			{
				Cs[r][c]->setPiece(new bishop(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'g')
			{
				Cs[r][c]->setPiece(new goldGen(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 's')
			{
				Cs[r][c]->setPiece(new silverGen(r, c, pieceColor, this, prom));
			}

			else if (tolower(pieceChar) == 'n')
			{
				Cs[r][c]->setPiece(new knight(r, c, pieceColor, this, prom));
			}

			else
				Cs[r][c]->setPiece(nullptr);
		}

	}
}

Board::~Board()
{
	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			delete Cs[r][c];
		}
	}
}
