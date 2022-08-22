#include "shogi.h"
#include"Board.h"
#include"Player.h"
#include"Piece.h"
#include"Cell.h"
#include"Timer.h"
#include"Pawn.h"
#include"Lance.h"
#include"King.h"
#include"bishop.h"
#include"rook.h"
#include"goldGen.h"
#include"silverGen.h"
#include"knight.h"
#include"capCells.h"
#include<thread>
#include<iomanip>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")

bool shogi::isTimerPaused = false;
bool shogi::isGameFinished = false;
int getPieceType(Piece* P);
void getRowColByMouse(int& r, int& c);
void stringInput(string& entered, int iX, int iY);
void removeScreensFromEnd(string& content, int N);


void shogi::displayTime()
{

	while (Ps[0]->getTime() == Timer{ -1,-1 })
	{
		if (isGameFinished)
		{
			return;
		}
	}

	checkAndDispTimeBox();


	delay(500);
	Ps[0]->displayTime();
	Ps[1]->displayTime();

	Timer Zero(0, 0);

	while (Ps[0]->getTime() != Zero && Ps[1]->getTime() != Zero)
	{
		if (!isTimerPaused)
		{
			Ps[turn]->decrementTime();
			Ps[turn]->displayTime();
			delay(1000);
		}
		if (isGameFinished)
			return;
	}
	isGameFinished = true;
}

bool shogi::endScreenDisplay(int Case)
{

	if (Case == 0)
		return true;
	int ws = initwindow(600, 400, "", 300, 200);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);//gold color
	setbkcolor(BLACK);
	readimagefile("extras/fbg.jpg", 0, 0, 600, 400);
	printImage(pureblack1, 10, 20, 580, 110);


	//exit button
	printImage(pureblack1, 50, 320, 200, 375);
	bgiout << "EXIT";
	outstreamxy(93, 335);


	//replay button
	printImage(pureblack1, 400, 320, 550, 375);
	bgiout << "REPLAY";
	outstreamxy(435, 335);

	if (Case == 1)
	{
		bgiout << "BLACK WON BY CHECKMATE!";
		outstreamxy(130, 50);
	}
	else if (Case == 2)
	{
		bgiout << "WHITE WON BY CHECKMATE!";
		outstreamxy(130, 50);
	}
	else if (Case == 3)
	{

		bgiout << "GAME ENDS IN STALEMATE!";
		outstreamxy(130, 50);
	}
	else if (Case == 4)
	{
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
		bgiout << "BLACK WON DUE TO TIME!";
		outstreamxy(130, 50);
	}
	else if (Case == 5)
	{
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
		bgiout << "WHITE WON DUE TO TIME!";
		outstreamxy(130, 50);
	}
	else if (Case == 6)
	{
		int pointsB = 0, pointsW = 0;

		readimagefile("extras/gribbon.gif", -50, 180, 250, 245);
		readimagefile("extras/gribbon.gif", 350, 180, 700, 245);

		string msg;
		calculatePoints(pointsB, pointsW);

		msg = (pointsB < 24 ? "BLACK LOST THE GAME!" : pointsW < 24 ? "WHITE LOST THE GAME!" : "GAME ENDS IN A DRAW!");

		bgiout << msg;
		outstreamxy(135, 50);

		settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
		//show white points
		bgiout << "WHITE'S POINTS: " << pointsW;
		outstreamxy(10, 200);
		//show black points
		bgiout << "BLACK'S POINTS: " << pointsB;
		outstreamxy(370, 200);
	}


	int r, c;
	while (true)
	{
		getmouseclick(WM_LBUTTONDOWN, c, r);
		//Exit button
		if (c >= 50 && c <= 200 && r >= 320 && r <= 375)
		{
			break;
		}
		//replay button
		else if (c >= 400 && c <= 550 && r >= 320 && r <= 375)
		{
			closegraph(ws);
			setcurrentwindow(mainW);
			replay();

			string content;
			std::ifstream fin("textfiles/replay.txt");
			getline(fin, content, '\0');

			//removing last screen from the content
			removeScreensFromEnd(content, 1);

			std::ofstream fout("textFiles/replay.txt");
			fout << content;

			return false;
		}
	}


	closegraph(ws);
	return true;

}

shogi::~shogi()
{
	freeAllMemory();
}



void shogi::loadNewGame(std::ifstream& fin)
{

	this->B = new Board(fin);
}

void shogi::loadSavedGame(std::ifstream& fin)
{

	Timer T;
	string name;


	fin >> turn;
	fin.ignore();
	std::getline(fin, name);
	fin >> T;
	this->Ps[0] = new Player(name, Color::BLACK, T);

	fin.ignore();
	std::getline(fin, name);
	fin >> T;
	this->Ps[1] = new Player(name, Color::WHITE, T);


	this->B = new Board(fin);
	this->sri = 0, this->sci = 0, this->dci = 0, this->dri = 0;

	loadCaptured(fin);
}

void shogi::loadCaptured(std::ifstream& fin)
{
	int size = 0;
	for (int p = 0; p < 2; p++)
	{
		int r = (p ? wcpRow : bcpRow);

		//for Pawn
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new Pawn(r, cpCol, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//for lance
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new Lance(r, cpCol + 1, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//for Rook
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new rook(r, cpCol + 2, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//for silver general
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new silverGen(r, cpCol + 3, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//FOR gold general
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new goldGen(r, cpCol + 4, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//for bishop
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new bishop(r, cpCol + 5, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
		//for knight
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			Piece* P = new knight(r, cpCol + 6, Ps[p]->getColor(), B);
			push_backCapPiece(P, p);
		}
	}
}

void shogi::saveInUndo(Timer T1, Timer T2)
{
	std::ofstream fout("TextFiles/undo.txt");
	fout << turn << endl;

	fout << T1 << endl;
	fout << T2 << endl;

	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			Piece* P = B->getPiece(ri, ci);
			if (P == nullptr)
			{
				fout << "- ";
			}
			else
			{
				fout << P->getPieceChar();
				fout << (P->isPiecePromoted() ? ". " : " ");
			}


		}
		fout << endl;
	}
	for (int ri = 0; ri < 2; ri++)
	{
		for (int t = 0; t < 7; t++)
		{
			fout << capturedPieces[ri][t]->size() << ' ';
		}
		fout << endl;
	}
}

void shogi::saveGame()
{
	std::ifstream fin("TextFiles/replay.txt");

	string primary;
	getline(fin, primary, '\0');

	removeScreensFromEnd(primary, 1);
	fin.close();

	std::ofstream fout("TextFiles/sReplay.txt");
	fout << primary;

	overWriteToFile("textfiles/saved.txt");
}

void shogi::restartGame()
{
	//if user confirms to proceed then restart implementation begins else just return
	if (confirmationMenu())
	{
		bool timerStatus = isTimerPaused;
		isTimerPaused = true;
		delay(500);
		closegraph(mainW);

		//memory cleanup
		B->freeBoardPieces();
		for (int p = 0; p < 2; p++)
		{
			for (int i = 0; i < 7; i++)
			{
				capturedPieces[p][i]->freeMemoryOfPieces();
			}
		}
		//resetting timers to -1,-1
		Ps[0]->setTime({ -1, -1 });
		Ps[1]->setTime({ -1, -1 });

		//loading board from the file
		std::ifstream fin("TextFiles/newgame.txt");
		loadNewGame(fin);

		//initializing  a screen before

		int wId = initwindow(900, 600, "Shogi", 150, 0);
		readimagefile("extras/fbg.jpg", 0, 0, 900, 600);

		//asking user for timebased game
		if (timeBasedOrNotScreen())
		{
			//setting the time
			int min = 10, sec = 0;

			setTimeScreen(min, sec);

			Timer T(min, sec);

			Ps[0]->setTime(T);
			Ps[1]->setTime(T);
			timerStatus = false;
		}

		//creating the new game window and setting it
		mainW = initwindow(getmaxwidth(), getmaxheight(), "", 0, 0);
		closegraph(wId);
		setcurrentwindow(mainW);
		display_Init();
		turnMsg(Ps[turn]);

		//display time only when the timer is not -1,-1
		if (Ps[0]->getTime() != Timer{ -1,-1 })
		{
			checkAndDispTimeBox();

			Ps[0]->displayTime();
			Ps[1]->displayTime();

			isTimerPaused = timerStatus;
		}
		//emptying the replay file and filling it with
		overWriteToFile("TextFiles/replay.txt");
	}
}

void shogi::freeAllMemory()
{
	delete Ps[0];
	delete Ps[1];
	delete B;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			capturedPieces[i][j]->freeMemoryOfPieces();
			delete capturedPieces[i][j];
		}
	}
}

void shogi::display_Init()
{
	readimagefile("extras/gbg.jpg", 0, 0, getmaxx(), getmaxy());

	readimagefile("extras/restart.gif", 18 * bLen, 5, 18 * bLen + bLen, bLen + 5);
	readimagefile("extras/save.gif", 18 * bLen, bLen + 20, 18 * bLen + bLen, 20 + bLen + bLen);
	readimagefile("extras/undo.gif", 18 * bLen, 2 * bLen + 40, 18 * bLen + bLen, 40 + 3 * bLen);
	readimagefile("extras/mainmenu.gif", 18 * bLen, 3 * bLen + 60, 18 * bLen + bLen, 60 + 4 * bLen);

	readimagefile("extras/tag.gif", 650, 570, 1080, 630);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);

	//replay button
	printImage(pureblack1, 660, 580, 830, 620);

	bgiout << "REPLAY";
	outstreamxy(700, 587);

	//impasee button
	printImage(pureblack1, 880, 580, 1070, 620);

	bgiout << "IMPASSE";
	outstreamxy(920, 587);

	//fading behing captured pieces
	readimagefile("extras/brown.gif", cpCol * bLen - 30, bcpRow * bLen, (cpCol + 7) * bLen + 30, bcpRow * bLen + bLen);
	readimagefile("extras/brown.gif", cpCol * bLen - 30, wcpRow * bLen, (cpCol + 7) * bLen + 30, wcpRow * bLen + bLen);

	B->displayBoard();
	disp_All_Captured(0);
	disp_All_Captured(1);
	disp_All_Cap_Count(0);
	disp_All_Cap_Count(1);

}

void shogi::checkAndDispTimeBox()
{
	if (Ps[0]->getTime() != Timer{ -1,-1 })
	{
		printImage(pureblack1, 13 * bLen - 48, 6 * bLen - 40, 13 * bLen + 100, 6 * bLen + 8);
		printImage(pureblack1, 13 * bLen - 48, 2 * bLen - 30, 13 * bLen + 100, 2 * bLen + 18);
	}
}






void shogi::selectCoord(int& r, int& c)
{
	while (!ismouseclick(WM_LBUTTONDOWN) && !isGameFinished);

	getmouseclick(WM_LBUTTONDOWN, c, r);

	if ((r <= 9 * bLen && r >= 0 && c >= 0 && c <= 9 * bLen) || ((r >= bcpRow * bLen && r <= (bcpRow + 1) * bLen || r >= wcpRow * bLen && r <= (wcpRow + 1) * bLen) && (c >= cpCol * bLen && c <= (cpCol + 7) * bLen)))
	{
		r /= bLen, c /= bLen;
	}

}

bool shogi::is_InsideBoard(int r, int c)
{
	return (r >= 0 && r <= 8 && c >= 0 && c <= 8);
}

int shogi::firstScreen()
{
	int wId = initwindow(900, 600, "WELCOME TO SHOGI", 150, 0);

	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);

	readimagefile("extras/fbg.jpg", 0, 0, 900, 600);
	printImage(pureblack1, 150, 50, 750, 150);

	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);
	bgiout << "SHOGI";
	outstreamxy(330, 75);


	printImage(pureblack1, 300, 250, 560, 250 + bLen);
	printImage(pureblack1, 300, 350, 560, 350 + bLen);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);



	bgiout << "NEW GAME";
	outstreamxy(352, 265);

	bgiout << "RESUME";
	outstreamxy(370, 365);
	return wId;
}

bool shogi::timeBasedOrNotScreen()
{
	int r, c;

	readimagefile("extras/fbg.jpg", 0, 0, 900, 600);
	printImage(pureblack1, 330, 200, 570, 265);
	printImage(pureblack1, 330, 300, 570, 365);

	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);

	bgiout << "TIMED GAME";
	outstreamxy(375, 220);

	bgiout << "TIME FREE";
	outstreamxy(380, 320);
	while (true)
	{
		getRowColByMouse(r, c);
		if (c >= 350 && c <= 550)
		{
			if (r >= 200 && r <= 265)
			{
				return true;
			}
			else if (r >= 300 && r <= 365)
			{
				return false;
			}
		}
	}
}

void shogi::setTimeScreen(int& min, int& sec)
{

	readimagefile("extras/fbg.jpg", 0, 0, 900, 600);

	//ok button
	printImage(pureblack1, 325, 380, 505, 425);

	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);

	bgiout << "OK!";
	outstreamxy(390, 387);

	//setTime board
	printImage(pureblack1, 210, 100, 610, 165);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	bgiout << "SET TIME";
	outstreamxy(310, 117);

	settextstyle(BOLD_FONT, HORIZ_DIR, 5);


	readimagefile("extras/up.gif", 360, 220, 380, 240);
	readimagefile("extras/up.gif", 430, 220, 450, 240);

	readimagefile("extras/down.gif", 360, 300, 380, 320);
	readimagefile("extras/down.gif", 430, 300, 450, 320);
	readimagefile("extras/tag.gif", 340, 242, 485, 300);
	int r, c;
	setcolor(WHITE);
	while (true)
	{
		bgiout << std::setw(2) << std::setfill('0') << min << ":" << std::setw(2) << std::setfill('0') << sec;
		outstreamxy(350, 250);

		getmouseclick(WM_LBUTTONDOWN, c, r);
		//down case
		if (r >= 300 && r <= 320)
		{
			//min case
			if (c >= 360 && c <= 380)
			{
				min = (min > 1 ? --min : min);
			}
			//second case
			else if (c >= 430 && c <= 450)
			{
				sec = (sec > 0 ? sec - 5 : 55);
			}
		}
		//up case
		else if (r >= 220 && r <= 240)
		{
			//min case
			if (c >= 360 && c <= 380)
			{
				min = (min >= 1 ? ++min : min);
			}
			//sec case
			else if (c >= 430 && c <= 450)
			{
				sec = (sec < 55 ? sec + 5 : 0);
			}
		}
		//ok case button
		else if (c >= 325 && c <= 505 && r >= 380 && r <= 425)
		{
			break;
		}

	}
}

void shogi::enterNameScreen(string& name1, string& name2)
{



	readimagefile("extras/fbg.jpg", 0, 0, 900, 600);

	printImage(pureblack1, 200, 50, 700, 155);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 3);
	bgiout << "BLACK'S  PLAYER";
	outstreamxy(310, 70);
	bgiout << "NAME :";
	outstreamxy(380, 110);

	readimagefile("extras/tag.gif", 340, 240, 570, 280);


	//text box 1
	setcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	bgiout << "               ";
	outstreamxy(350, 250);

	stringInput(name1, 350, 250);

	printImage(pureblack1, 200, 50, 700, 155);

	setcolor(GOLD_COLOR);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 3);
	bgiout << "WHITE'S  PLAYER";
	outstreamxy(310, 70);
	bgiout << "NAME :";
	outstreamxy(380, 110);


	//text box 2
	setcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	bgiout << "               ";
	outstreamxy(350, 250);

	stringInput(name2, 350, 250);
}

void shogi::saveMessageBox()
{
	bool timerStatus = isTimerPaused;
	isTimerPaused = true;
	int w = initwindow(500, 200, "", 350, 250);

	readimagefile("extras/fbg.jpg", 0, 0, 500, 200);
	//save confirmation message
	printImage(pureblack1, 40, 40, 450, 140);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);

	bgiout << "YOUR GAME HAS BEEN";
	outstreamxy(110, 65);
	bgiout << "SAVED!";
	outstreamxy(200, 95);

	while (!ismouseclick(WM_LBUTTONDOWN));

	closegraph(w);
	setcurrentwindow(mainW);
	isTimerPaused = timerStatus;

}


bool shogi::isClickOnSaveBtn(int r, int c)
{
	//readimagefile("extras/save.gif", 18 * bLen, bLen + 20, 18 * bLen + bLen, 20 + bLen + bLen);

	if (c >= 18 * bLen && c <= 19 * bLen && r >= bLen + 20 && r <= 20 + 2 * bLen)
	{
		return true;
	}
	return false;
}

bool shogi::isClickOnRestartBtn(int r, int c)
{
	//readimagefile("extras/restart.gif", 18 * bLen, 5, 18 * bLen + bLen, bLen+5);
	if (c >= 18 * bLen && c <= 19 * bLen && r >= 5 && r <= bLen + 5)
	{
		return true;
	}
	return false;
}

bool shogi::isClickOnUndoBtn(int r, int c)
{
	//readimagefile("extras/undo.gif", 18 * bLen, 2*bLen + 40, 18 * bLen + bLen, 40 + 3*bLen );
	if (c >= 18 * bLen && c <= 19 * bLen && r >= 2 * bLen + 40 && r <= 40 + 3 * bLen)
	{
		return true;
	}
	return false;
}

bool shogi::isClickOnReturnButton(int r, int c)
{
	//readimagefile("extras/mainmenu.gif", 18 * bLen, 3*bLen + 60, 18 * bLen + bLen, 60 + 4*bLen);
	if (c >= 18 * bLen && c <= 19 * bLen && r >= 3 * bLen + 60 && r <= 4 * bLen + 60)
	{
		return true;
	}
	return false;
}

bool shogi::isClickOnReplay(int r, int c)
{
	//readimagefile("extras/replay.gif", 660, 580,830, 620);
	if (c >= 660 && c <= 830 && r >= 580 && r <= 620)
	{
		return true;
	}
	return false;
}

bool shogi::isClickOnImpasse(int r, int c)
{
	//printImage(pureblack1, 880, 580, 1070, 620);
	if (c >= 880 && c <= 1070 && r >= 580 && r <= 620)
	{
		return true;
	}
	return false;
}

void shogi::overWriteToFile(const string& filename)
{
	std::ofstream fout(filename);
	saveInFile(fout);
}

void shogi::saveInFile(std::ofstream& fout)
{
	fout << turn << endl;

	fout << Ps[0]->getName() << endl << Ps[0]->getTime() << endl;
	fout << Ps[1]->getName() << endl << Ps[1]->getTime() << endl;




	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			Piece* P = B->getPiece(ri, ci);
			if (P == nullptr)
			{
				fout << "-  ";
			}
			else
			{

				fout << P->getPieceChar();
				fout << (P->isPiecePromoted() ? ". " : "  ");

			}


		}
		fout << endl;
	}
	for (int ri = 0; ri < 2; ri++)
	{
		for (int t = 0; t < 7; t++)
		{
			fout << capturedPieces[ri][t]->size() << ' ';
		}
		fout << endl;
	}
}




void shogi::undoMove()
{

	std::ifstream fin("TextFiles/replay.txt");
	

	string primary;
	getline(fin, primary,'\0');

	removeScreensFromEnd(primary, 1);
	fin.close();

	std::ofstream fout("TextFiles/replay.txt");
	fout << primary;






	fin.open("TextFiles/undo.txt");
	Timer T;
	B->freeBoardPieces();

	fin >> turn;

	fin >> T;
	Ps[0]->setTime(T);

	fin >> T;
	Ps[1]->setTime(T);

	B->loadBoardPieces(fin);
	//freeing the memory of all the captured pieces

	for (int r = 0; r < 2; r++)
	{
		for (int i = 0; i < 7; i++)
		{
			capturedPieces[r][i]->freeMemoryOfPieces();
		}
	}


	loadCaptured(fin);

	Ps[0]->displayTime();
	Ps[1]->displayTime();

	B->displayBoard();

	markKingAsChecked();
	disp_All_Captured(0);
	disp_All_Cap_Count(0);
	disp_All_Captured(1);
	disp_All_Cap_Count(1);

	turnMsg(Ps[turn]);

}

bool shogi::confirmationMenu()
{
	bool timerStatus = isTimerPaused;
	isTimerPaused = true;
	int ws = initwindow(500, 300, "", 400, 200);
	readimagefile("extras/fbg.jpg", 0, 0, 500, 300);

	//confirmation msg
	printImage(pureblack1, 50, 20, 450, 130);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);
	bgiout << "DO YOU WANT TO";
	outstreamxy(145, 50);

	bgiout << "TO PROCEED ?";
	outstreamxy(170, 80);


	//ok button
	printImage(pureblack1, 80, 200, 200, 250);

	bgiout << "OK !";
	outstreamxy(120, 215);

	//cancel button
	printImage(pureblack1, 300, 200, 430, 250);

	bgiout << "CANCEL";
	outstreamxy(322, 215);

	int r, c;
	bool decision;
	while (true)
	{
		getRowColByMouse(r, c);
		if (r >= 200 && r <= 250)
		{
			//ok button
			if (c >= 80 && c <= 200)
			{
				decision = true;
				break;
			}
			//cancel button
			else if (c >= 300 && c <= 430)
			{
				decision = false;
				break;
			}
		}
	}


	closegraph(ws);
	setcurrentwindow(mainW);

	isTimerPaused = timerStatus;

	return decision;
}






shogi::shogi(const std::string& filename)
{
	//initialization of capturedPieces

	for (int r = 0; r < 2; r++)
	{
		int row = (r == 1 ? wcpRow : bcpRow);
		for (int i = 0; i < 7; i++)
		{
			capturedPieces[r][i] = new capCell(row, (cpCol + i), COLOR(255, 223, 128));
		}
	}

	std::ifstream fin(filename);
	if (filename == "textfiles/newgame.txt")
	{
		string name1, name2;


		loadNewGame(fin);

		enterNameScreen(name1, name2);

		Ps[0] = new Player(name1, Color::BLACK, { -1,-1 });
		Ps[1] = new Player(name2, Color::WHITE, { -1,-1 });
		turn = 1, sri = -1, sci = -1, dri = -1, dci = -1;

		Ps[0]->setName(name1);
		Ps[1]->setName(name2);

		if (timeBasedOrNotScreen())
		{
			int min = 10, sec = 0;

			setTimeScreen(min, sec);

			Timer T(min, sec);

			Ps[0]->setTime(T);
			Ps[1]->setTime(T);

		}

	}
	else
	{
		loadSavedGame(fin);
	}
}



void shogi::turnMsg(Player* P)
{
	isGameFinished = false;
	printImage(pureblack1, 670, 2, 1000, 85);

	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);//gold color
	setbkcolor(BLACK);//black color

	bgiout << "TURN:";
	bgiout << (turn == 0 ? "(BLACK)" : "(WHITE)");
	outstreamxy(735, 15);
	bgiout << P->getName();
	outstreamxy(735, 48);
}



bool shogi::validPieceSelection()
{
	return B->validPieceSelection(Ps[turn], sri, sci);
}

bool shogi::validDestSelection()
{
	return B->validDestSelection(Ps[turn], dri, dci);
}



void shogi::turnChange()
{
	turn = (turn + 1) % 2;
}

void shogi::highlightValidCells()
{
	B->highlightCell(sri, sci);
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			if (B->validDestSelection(Ps[turn], ri, ci) && B->isLegalMove(sri, sci, ri, ci) &&
				!B->selfCheck(sri, sci, ri, ci, turn))
			{
				B->highlightCell(ri, ci);
			}
		}
	}
}

void shogi::unhighlightCells()
{
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			if ((B->getCell(ri, ci)->getHighstat()))
			{
				B->getCell(ri, ci)->unhighLight();
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		//Ps[turn]->unhighlight_Cell(i);
		capturedPieces[turn][i]->unhighLight();
	}
}

bool shogi::isCheck()
{
	return B->isCheck(turn);
}

bool shogi::selfCheck()
{
	return B->selfCheck(sri, sci, dri, dci, turn);
}

void shogi::addCapPiece()
{
	Piece* P = B->getPiece(dri, dci);
	if (P != nullptr && P->getColor() != Ps[turn]->getColor())
	{
		int type = getPieceType(P);
		int r = (P->getColor() == Color::WHITE ? bcpRow : wcpRow);
		P->move(r, cpCol + type);
		/*Ps[turn]->push_backPiece(P);
		Ps[turn]->disp_Cap_Count_Of(type);*/
		push_backCapPiece(P, turn);
		capturedPieces[turn][type]->disp_Cap_Number();

		P->setColor(Ps[turn]->getColor());
		//Ps[turn]->disp_Captured(type);
		capturedPieces[turn][type]->draw();
	}
}

void shogi::drawTwoPieces()
{
	if (sri >= 0 && sri < 9 && sci >= 0 && sci < 9)
		B->drawPiece(sri, sci);

	if (dri >= 0 && dri < 9 && dci >= 0 && dci < 9)
		B->drawPiece(dri, dci);
}

bool shogi::is_Valid_CapPiece_Select(int r, int c)
{

	int validR = (Ps[turn]->getColor() == Color::WHITE ? wcpRow : bcpRow);

	if (r == validR && c >= 10 && c <= 17)
	{
		//return Ps[turn]->isPiece_Present(c - 10);
		return capturedPieces[turn][c - 10]->size() != 0;
	}
	return false;
}

bool shogi::isAnyMoveAvailable()
{
	bool condition = B->isAnyMoveAvailable(Ps[turn], turn);

	if (condition)
		return condition;


	//checking if the dropped piece can remove the check

	for (int i = 0; i < 7; i++)
	{
		if (capturedPieces[turn][i]->size() != 0)
		{
			Piece* P = capturedPieces[turn][i]->getPiece();
			for (int dr = 0; dr < 9; dr++)
			{
				for (int dc = 0; dc < 9; dc++)
				{
					if (B->isLegalDrop(P, Ps[!turn], turn, dr, dc) && !B->selfCheckAfterDrop(P, dr, dc, turn))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool shogi::isLegalDrop(int type)
{
	if (type > 7 || type < 0)
		return false;
	//Piece* P = Ps[turn]->extractPiece(type);

	Piece* P = capturedPieces[turn][type]->getPiece();

	return is_InsideBoard(dri, dci) && B->isLegalDrop(P, Ps[!turn], turn, dri, dci) && !B->selfCheckAfterDrop(P, dri, dci, turn);
}

void shogi::highlightValidDropCells(int type)
{
	//Piece* P = Ps[turn]->extractPiece(type);
	Piece* P = capturedPieces[turn][type]->getPiece();
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{

			if (B->isLegalDrop(P, Ps[!turn], turn, ri, ci) && !B->selfCheckAfterDrop(P, ri, ci, turn))
			{
				B->highlightCell(ri, ci);
			}
		}
	}
}

void shogi::drop_Cap_Piece_On_Board(int type)
{
	//Piece* P = Ps[turn]->extractPiece(type);
	Piece* P = capturedPieces[turn][type]->getPiece();
	P->move(dri, dci);
	B->getCell(dri, dci)->setPiece(P);
	P->setColor(Ps[turn]->getColor());
	//Ps[turn]->pop_backPiece(type);
	capturedPieces[turn][type]->pop_Piece();
}

void shogi::promotionHandler()
{
	int height = 2 * bLen, width = bLen;

	int top = (dri < 1 ? (dri + 1) * bLen + 30 : dri>7 ? (dri - 1) * bLen + 30 : dri * bLen + 30);
	int left = (dci + 1) * bLen;

	Piece* SP = B->getPiece(dri, dci);
	if (SP->isPiecePromoted())
		return;

	int prom_decision = SP->promotion_status(dri);

	//Promotion with respect to its destination
	if (prom_decision != 0)
	{

		if (prom_decision == 1)
		{
			int r, c;
			int w = initwindow(width, height, "", left, top);
			readimagefile("extras/wooden.gif", 0, 0, getmaxx(), getmaxy());
			SP->norm_image_at(0, 0);
			SP->prom_image_at(1, 0);
			selectCoord(r, c);
			if (r == 1)
			{
				SP->promote(true);
				setcurrentwindow(mainW);
				B->getCell(dri, dci)->draw();
			}
			closegraph(w);
			setcurrentwindow(mainW);
		}
		else if (prom_decision == 2)
		{
			SP->promote(true);
			B->getCell(dri, dci)->draw();
		}

	}


	// promotion with respect to its starting position
	else
	{
		prom_decision = SP->promotion_status(sri);
		if (prom_decision == 1)
		{
			int r, c;
			top = (dri - 1) * bLen + 30;
			int w = initwindow(width, height, "", left, top);
			readimagefile("extras/fbg.jpg", 0, 0, getmaxx(), getmaxy());
			SP->norm_image_at(0, 0);
			SP->prom_image_at(1, 0);
			selectCoord(r, c);
			if (r == 1)
			{
				SP->promote(true);
				setcurrentwindow(mainW);
				B->getCell(dri, dci)->draw();
			}
			closegraph(w);
			setcurrentwindow(mainW);

		}
		else if (prom_decision == 2)
		{
			SP->promote(true);
			B->getCell(dri, dci)->draw();
		}
	}

	/*this time is displayed because when asked for promotion timer in background
	stops printing but not in memory and it should not be stopped so at the end of promotion
	i print the current players latest timer*/
	if (Ps[turn]->getTime() != Timer{ -1,-1 })
		Ps[turn]->displayTime();
}

bool shogi::isImpasse()
{

	int krB = 0, kcB = 0, krW = 0, kcW = 0;
	B->findKing(krB, kcB, 0);
	B->findKing(krW, kcW, 1);

	//if both kings have reached enemys promotion zone
	if (krW <= 2 && krB >= 6)
	{
		return true;
	}

	return false;
}

void shogi::calculatePoints(int& player1, int& player2)
{
	int points = 0;

	//on board pieces
	for (int ri = 0; ri < 9; ri++)
	{
		for (int ci = 0; ci < 9; ci++)
		{
			Piece* P = B->getPiece(ri, ci);
			if (P != nullptr)
			{
				char type = P->getPieceChar();
				if (islower(type))
				{
					if (type == 'r' || type == 'b')
					{
						player1 += 5;
					}
					else if (type != 'k')
					{
						player1 += 1;
					}
				}
				else
				{
					if (type == 'R' || type == 'B')
					{
						player2 += 5;
					}
					else if (type != 'K')
					{
						player2 += 1;
					}
				}
			}
		}
	}

	//In captured pieces

	for (int p = 0; p < 2; p++)
	{
		for (int type = 0; type < 7; type++)
		{
			int score = 0;
			if (type == 2 || type == 5)//rook and bishops
			{
				score = 5 * capturedPieces[p][type]->size();
			}
			else
			{
				score = capturedPieces[p][type]->size();
			}
			p == 0 ? player1 += score : player2 += score;
		}
	}
}

void shogi::markKingAsChecked()
{

	static int oldKrWhite = -1, oldKcWhite = -1, oldColorWhite = -1;
	static int oldKrBlack = -1, oldKcBlack = -1, oldColorBlack = -1;
	int krW, kcW, krB, kcB;

	//resetting the old box for white king
	if (oldKrWhite != -1 && oldKcWhite != -1) //means old king has never been reset means no check before
	{
		B->getCell(oldKrWhite, oldKcWhite)->setColor(oldColorWhite);
		B->getCell(oldKrWhite, oldKcWhite)->draw();
	}
	//resetting the old box for black king
	if (oldKrBlack != -1 && oldKcBlack != -1) //means old king has never been reset means no check before
	{
		B->getCell(oldKrBlack, oldKcBlack)->setColor(oldColorBlack);
		B->getCell(oldKrBlack, oldKcBlack)->draw();
	}
	//if check by black then highlight whites king
	if (B->isCheck(0))
	{
		B->findKing(krW, kcW, 1);
		oldColorWhite = B->getCell(krW, kcW)->getColor();
		B->getCell(krW, kcW)->setColor(COLOR(255, 71, 26));
		B->getCell(krW, kcW)->draw();
		oldKrWhite = krW, oldKcWhite = kcW;
	}
	//if check by white king then highlight blacks king
	else if (B->isCheck(1))
	{
		B->findKing(krB, kcB, 0);
		oldColorBlack = B->getCell(krB, kcB)->getColor();
		B->getCell(krB, kcB)->setColor(COLOR(255, 71, 26));
		B->getCell(krB, kcB)->draw();
		oldKrBlack = krB, oldKcBlack = kcB;
	}

}



void shogi::push_backCapPiece(Piece* P, int turn)
{
	P->promote(false);
	int index = getPieceType(P);
	capturedPieces[turn][index]->push_Piece(P);
}

void shogi::disp_All_Captured(int r)
{
	for (int i = 0; i < 7; i++)
	{
		capturedPieces[r][i]->draw();
	}
}

void shogi::disp_All_Cap_Count(int r)
{
	for (int i = 0; i < 7; i++)
	{
		capturedPieces[r][i]->disp_Cap_Number();
	}
}



void shogi::replay()
{
	bool timerStatus = isTimerPaused;
	isTimerPaused = true;
	int currentScreen = 0, totalScreens = 0;

	std::ifstream fin("TextFiles/replay.txt");

	readimagefile("extras/gbg.jpg", 0, 0, getmaxwidth(), getmaxheight());
	readimagefile("extras/next.gif", 1000, 580, 1065, 645);
	readimagefile("extras/prev.gif", 800, 580, 865, 645);
	readimagefile("extras/resume.gif", 880, 550, 985, 645);

	//counting screens in replay.txt
	do
	{
		skipScreen(fin);
		totalScreens++;

	} while ((!fin.eof()));

	//subtracting one screen because it counts one extra
	totalScreens--;

	fin.close();
	fin.open("TextFiles/replay.txt");

	this->loadAndDrawScreen(fin);

	checkAndDispTimeBox();
	if (Ps[0]->getTime() != Timer{ -1,-1 })
	{
		Ps[0]->displayTime();
		Ps[1]->displayTime();
	}

	//displaying the currents screen box

	printImage(pureblack1, 700, 5, 1050, 65);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	setcolor(GOLD_COLOR);
	setbkcolor(BLACK);

	bgiout << "MOVE: " << std::setw(3) << std::setfill(' ') << currentScreen + 1
		<< " /" << std::setw(3) << std::setfill(' ') << totalScreens;

	outstreamxy(760, 20);

	int r, c;
	while (true)
	{
		getmouseclick(WM_LBUTTONDOWN, c, r);
		char e = 0;

		//Next button
		if (currentScreen < totalScreens - 1 && (c >= 1000 && c <= 1065 &&
			r >= 580 && r <= 645))
		{
			this->loadAndDrawScreen(fin);
			currentScreen++;
		}
		//prev button
		else if (currentScreen != 0 && (c >= 800 && c <= 865 && r >= 580 && r <= 645))
		{
			string content;
			currentScreen--;
			fin.close();
			fin.open("TextFiles/replay.txt");
			//skipping screens
			for (int i = 0; i < currentScreen; i++)
			{
				skipScreen(fin);
			}
			loadAndDrawScreen(fin);
		}
		//resume button
		else if (c >= 880 && c <= 985 && r >= 550 && r <= 645)
		{
			fin.close();
			fin.open("TextFiles/replay.txt");
			string primary = "", temp = "";

			for (int i = 0; i < (currentScreen + 1) * 16; i++)
			{
				std::getline(fin, temp);
				primary += temp;
				primary += '\n';
			}
			fin.close();
			std::ofstream fout("TextFiles/replay.txt");
			fout << primary;
			break;
		}
		//printing the Move status in case of valid click
		if (r != -1 && c != -1)
		{

			settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
			setcolor(GOLD_COLOR);
			setbkcolor(BLACK);

			bgiout << "MOVE: " << std::setw(3) << std::setfill(' ') << currentScreen + 1
				<< " /" << std::setw(3) << std::setfill(' ') << totalScreens;

			outstreamxy(760, 20);
			PlaySound(TEXT("extras/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
	}


	this->display_Init();
	turnMsg(Ps[turn]);
	if (Ps[0]->getTime() != Timer{ -1,-1 })
	{
		checkAndDispTimeBox();

		Ps[0]->displayTime();
		Ps[1]->displayTime();

		isTimerPaused = timerStatus;
	}

}

void shogi::loadAndDrawScreen(std::ifstream& fin)
{
	string fzool;
	Timer T;
	B->freeBoardPieces();

	fin >> turn;
	fin.ignore();
	getline(fin, fzool);

	fin >> T;
	Ps[0]->setTime(T);
	fin.ignore();
	getline(fin, fzool);

	fin >> T;
	Ps[1]->setTime(T);

	B->loadBoardPieces(fin);
	//freeing the memory of all the captured pieces

	for (int r = 0; r < 2; r++)
	{
		for (int i = 0; i < 7; i++)
		{
			capturedPieces[r][i]->freeMemoryOfPieces();
		}
	}


	loadCaptured(fin);

	Ps[0]->displayTime();
	Ps[1]->displayTime();

	B->displayBoard();

	markKingAsChecked();
	disp_All_Captured(0);
	disp_All_Cap_Count(0);
	disp_All_Captured(1);
	disp_All_Cap_Count(1);
}


void shogi::skipScreen(std::ifstream& fin)
{
	string content;
	//16 lines need to be skipped for skipping a screen
	for (int i = 0; i < 16; i++)
	{
		std::getline(fin, content);
		content = "";
	}
}








void shogi::play()
{
	std::ofstream Rout("TextFiles/replay.txt", std::ios::app);
	display_Init();
	bool isExit = false;
	do
	{
		Timer Zero(0, 0), T1, T2;
		isGameFinished = false;
	
		if (Ps[0]->getTime() != Timer{ -1,-1 })
			isTimerPaused = false;
		//new thread for displaying time
		std::thread P1(&shogi::displayTime, this);


		bool isValid_Cap_Piece_Selected = false;
		bool isValid_Cap_Drop = false;
		bool hasAnyMoveH = false;//to prevent unnecessary undoing


		int type;
		int endingScreen = -1;

		do
		{
			//saving in replay.txt
			saveInFile(Rout);

			T1 = Ps[0]->getTime();
			T2 = Ps[1]->getTime();

			turnMsg(Ps[turn]);
			markKingAsChecked();//marks the king's box as red
			//if the player with current turn has no move available then finish the game
			if (!isAnyMoveAvailable())
			{
				break;
			}

			do
			{
				selectCoord(sri, sci);
				type = sci - cpCol;

				//	if user selects from the captured pieces
				isValid_Cap_Piece_Selected = is_Valid_CapPiece_Select(sri, sci);
				if (isValid_Cap_Piece_Selected)
				{
					//Ps[turn]->highlight_Cell(type);
					capturedPieces[turn][type]->highLight();
				}
				//if user saves the game
				else if (isClickOnSaveBtn(sri, sci))
				{

					saveGame();
					saveMessageBox();
				}
				//undo button
				else if (isClickOnUndoBtn(sri, sci))
				{
					if (hasAnyMoveH)
					{
						hasAnyMoveH = false;
						undoMove();
						T1 = Ps[0]->getTime();
						T2 = Ps[1]->getTime();
					}
				}
				//exit to mai menu
				else if (isClickOnReturnButton(sri, sci))
				{
					if (confirmationMenu())
					{
						endingScreen = 0;
						break;
					}
				}
				//restart button
				else if (isClickOnRestartBtn(sri, sci))
				{
					restartGame();
					T1 = Ps[0]->getTime();
					T2 = Ps[1]->getTime();
					hasAnyMoveH = false;
				}
				//replay button
				else if (isClickOnReplay(sri, sci))
				{
					replay();
					T1 = Ps[0]->getTime();
					T2 = Ps[1]->getTime();
					hasAnyMoveH = false;
				}
				//click on impasse
				else if(isClickOnImpasse(sri,sci))
				{
					if (isImpasse() && !B->isCheck(turn) && !B->isCheck((turn + 1) % 2) && confirmationMenu())
					{
						endingScreen = 6;
						break;
					}
				}
				else if (isGameFinished)
				{
					endingScreen = (Ps[0]->getTime() == Zero ? 5 : 4);
					break;
				}

			} while (!(validPieceSelection() || isValid_Cap_Piece_Selected));

			if (endingScreen != -1)
			{
				break;
			}
			if (isValid_Cap_Piece_Selected)
			{
				highlightValidDropCells(type);
			}
			else
			{
				highlightValidCells();
			}



			//second mouse click
			do
			{

				selectCoord(dri, dci);

				type = sci - cpCol;

				isValid_Cap_Piece_Selected = is_Valid_CapPiece_Select(dri, dci);
				isValid_Cap_Drop = isLegalDrop(type);

				//If users selects a Piece instead of Destination

				if (B->validPieceSelection(Ps[turn], dri, dci) && !(sri == dri && dci == sci))
				{
					unhighlightCells();
					sri = dri, sci = dci;
					highlightValidCells();
				}

				//save button click
				else if (isClickOnSaveBtn(dri, dci))
				{
					saveGame();
					saveMessageBox();
				}

				//undo button
				else if (isClickOnUndoBtn(dri, dci))
				{
					if (hasAnyMoveH)
					{
						hasAnyMoveH = false;
						undoMove();
						T1 = Ps[0]->getTime();
						T2 = Ps[1]->getTime();
					}
				}
				//main menu button click
				else if (isClickOnReturnButton(dri, dci))
				{
					if (confirmationMenu())
					{
						endingScreen = 0;
						break;
					}
				}
				//restart button
				else if (isClickOnRestartBtn(dri, dci))
				{
					restartGame();
					T1 = Ps[0]->getTime();
					T2 = Ps[1]->getTime();
					hasAnyMoveH = false;
				}
				//replay button
				else if (isClickOnReplay(dri, dci))
				{
					replay();
					T1 = Ps[0]->getTime();
					T2 = Ps[1]->getTime();
					hasAnyMoveH = false;
				}
				//click on impasse button
				else if (isClickOnImpasse(dri, dci))
				{
					if (isImpasse() && !B->isCheck(turn) && !B->isCheck((turn + 1) % 2) && confirmationMenu())
					{
						endingScreen = 6;
						break;
					}
				}
				//if user has selected a valid captured Piece
				else if (isValid_Cap_Piece_Selected)
				{
					type = dci - cpCol;
					unhighlightCells();
					//Ps[turn]->highlight_Cell(type);
					capturedPieces[turn][type]->highLight();
					highlightValidDropCells(type);
					sri = dri, sci = dci;
				}

				//if user has selected a valid drop location

				else if (isValid_Cap_Drop)
				{
					saveInUndo(T1, T2);
					drop_Cap_Piece_On_Board(type);


					capturedPieces[turn][type]->unhighLight();

					//displaying updated info
					capturedPieces[turn][type]->draw();
					capturedPieces[turn][type]->disp_Cap_Number();

					break;
				}
				
				else if (isGameFinished)
				{
					endingScreen = (Ps[0]->getTime() == Zero ? 5 : 4);
					break;
				}

			} while (!(validDestSelection() && validPieceSelection() && B->isLegalMove(sri, sci, dri, dci) && !selfCheck()));

			if (endingScreen != -1)
			{
				break;
			}

			unhighlightCells();

			if (!isValid_Cap_Drop)
				saveInUndo(T1, T2);

			addCapPiece(); //adds any piece if captured to the respective Players array

			if (!isValid_Cap_Drop)//move only if the pieces from the board are moved
			{
				B->move(sri, sci, dri, dci);// Move in memory
			}



			drawTwoPieces(); //display The change on the screen for only two pieces

			if (!isValid_Cap_Drop) //promote only if piece is moved onto the board, not when dropped from the captured
			{
				promotionHandler(); //this asks for promotion or forces the promotion if any piece needs promotion
			}


			turnChange(); //turn change
			PlaySound(TEXT("extras/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			hasAnyMoveH = true;
		} while (true);

		isGameFinished = true;
		P1.join();

		if (endingScreen == -1)
		{
			turnChange();
			bool check = B->isCheck(turn);
			if (check)
			{
				endingScreen = (turn == 0 ? 1 : 2);
			}
			//stalemate
			else if (!check)
			{
				endingScreen = 3;
			}
		}

		isExit = this->endScreenDisplay(endingScreen);

	} while (!isExit);
}


