#pragma once
class Board;
class Player;
class Piece;
class capCell;
#include"Timer.h"
#include<fstream>
#include"utility.h"
class shogi
{
	int sri, sci, dri, dci,turn;
	Board* B;
	Player* Ps[2];
	capCell* capturedPieces[2][7];

	
	static bool isTimerPaused;//if anything pauses the timer
	
	static bool isGameFinished;//if the timer finishes of any player and game finishes so just exit all processes
	
	//this function pushes the given piece in its right index in the captured pieces of current turn's player
	void push_backCapPiece(Piece* P, int turn);

	//function displays all capPieces of specified row(0 for black, 1 for white)
	void disp_All_Captured(int r);

	//same as above just displays their count
	void disp_All_Cap_Count(int r);

	


	void loadNewGame(std::ifstream& fin);
	void loadSavedGame(std::ifstream& fin);
	void loadCaptured(std::ifstream& fin);
	//saveInUndo recieves Two Timers to set the time of the start of the move in undo.txt
	void saveInUndo(Timer T1, Timer T2);

	//save game in saved.txt
	void saveGame();
	
	void restartGame();

	void overWriteToFile(const string& filename);
	void saveInFile(std::ofstream& fout);


	void undoMove();

	bool confirmationMenu();

	void freeAllMemory();
	void display_Init();

	void checkAndDispTimeBox();
	//----
	static void selectCoord(int& r, int& c);
	static bool is_InsideBoard(int r, int c);
	
	static bool timeBasedOrNotScreen();
	static void setTimeScreen(int& min, int& sec);
	static void enterNameScreen(string& name1, string& name2);
	static void saveMessageBox();
	static bool isClickOnSaveBtn(int r, int c);
	static bool isClickOnRestartBtn(int r, int c);
	static bool isClickOnUndoBtn(int r, int c);
	static bool isClickOnReturnButton(int r, int c);
	static bool isClickOnReplay(int r, int c);
	static bool isClickOnImpasse(int r, int c);



	


	void replay();
	void loadAndDrawScreen(std::ifstream& fin);//function only for replay
	void skipScreen(std::ifstream& fin);

	void turnMsg(Player* P);

	bool validPieceSelection();
	bool validDestSelection();

	void turnChange();

	void highlightValidCells(); 
	void unhighlightCells();

	bool isCheck();
	bool selfCheck();

	void addCapPiece();

	void drawTwoPieces();

	bool is_Valid_CapPiece_Select(int r, int c);

	bool isAnyMoveAvailable();

	bool isLegalDrop(int type);
	void highlightValidDropCells(int type);//highlights valid drop cells of specified type
	void drop_Cap_Piece_On_Board(int type);//drops piece of specified type on the board

	void promotionHandler();

	//Impasse functions
	bool isImpasse();
	void calculatePoints(int &player1, int&player2);

	void markKingAsChecked();

	void displayTime();

	//returns true if the player exits to main menu
	bool endScreenDisplay(int Case);

public:
	
	shogi(const string& filename);

	static int firstScreen();

	//Play All Game
	//my play function will have exitScreen equal to => 0 if player exits to main menu, 1 if player 1 has won , 2 if player 2 has won, 3 in case of stalemate,4 if player 1 won due to time,5 if player 2 won due to time,6 for impasse
	void play();

	~shogi();
};

