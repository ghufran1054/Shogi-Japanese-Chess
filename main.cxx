#include"utility.h"
#include <iostream>
#include<iomanip>
using namespace std;
#include"Pawn.h"
#include"Lance.h"
#include"King.h"
#include"bishop.h"
#include"rook.h"
#include"goldGen.h"
#include"silverGen.h"
#include"knight.h"
#include"Cell.h"
#include"shogi.h"
LPPICTURE whiteNormal[8], whiteProm[6], blackNormal[8], blackProm[6],h_circle,
gBox, pureblack1;
int mainW = 0;

void loadPromPieces(LPPICTURE* Ps1, LPPICTURE* Ps2)
{
    storeImage(Ps1[0], "shogi pieces gifs/prompawnb.gif");
    storeImage(Ps1[1], "shogi pieces gifs/promlanceb.gif");
    storeImage(Ps1[2], "shogi pieces gifs/promrookb.gif");
    storeImage(Ps1[3], "shogi pieces gifs/promsilvergenb.gif");
    storeImage(Ps1[4], "shogi pieces gifs/prombishopb.gif");
    storeImage(Ps1[5], "shogi pieces gifs/promknightb.gif");



    storeImage(Ps2[0], "shogi pieces gifs/prompawnw.gif");
    storeImage(Ps2[1], "shogi pieces gifs/promlancew.gif");
    storeImage(Ps2[2], "shogi pieces gifs/promrookw.gif");
    storeImage(Ps2[3], "shogi pieces gifs/promsilvergenw.gif");
    storeImage(Ps2[4], "shogi pieces gifs/prombishopw.gif");
    storeImage(Ps2[5], "shogi pieces gifs/promknightw.gif");
}
void loadNormalPieces(LPPICTURE* Ps1, LPPICTURE* Ps2)
{
    storeImage(Ps1[0], "shogi pieces gifs/pawnb.gif");
    storeImage(Ps1[1], "shogi pieces gifs/lanceb.gif");
    storeImage(Ps1[2], "shogi pieces gifs/rookb.gif");
    storeImage(Ps1[3], "shogi pieces gifs/silvergenb.gif");
    storeImage(Ps1[4], "Shogi pieces gifs/goldgeneralb.gif");
    storeImage(Ps1[5], "shogi pieces gifs/bishopb.gif");
    storeImage(Ps1[6], "shogi pieces gifs/knightb.gif");
    storeImage(Ps1[7], "shogi pieces gifs/kingb.gif");


    storeImage(Ps2[0], "shogi pieces gifs/pawnw.gif");
    storeImage(Ps2[1], "shogi pieces gifs/lancew.gif");
    storeImage(Ps2[2], "shogi pieces gifs/rookw.gif");
    storeImage(Ps2[3], "shogi pieces gifs/silvergenw.gif");
    storeImage(Ps2[4], "Shogi pieces gifs/goldgeneralw.gif");
    storeImage(Ps2[5], "shogi pieces gifs/bishopw.gif");
    storeImage(Ps2[6], "shogi pieces gifs/knightw.gif");
    storeImage(Ps2[7], "shogi pieces gifs/kingw.gif");
}

void stringInput(string& entered, int iX, int iY)
{
    int input;
    moveto(iX, iY);
    bgiout << "|";
    outstream();
    input = getch();
    while (input != 13)
    {
        if (input == 8)
        {
            if (entered.length() != 0)
            {
                entered.pop_back();
                moveto(getx() - 28, 250);
                bgiout << "  ";
                outstream();
                moveto(getx() - 28, 250);
                bgiout << "|";
                outstream();
            }

        }
        else
        {
            if (entered.size() < 14)
            {
                moveto(getx() - 14, iY);
                bgiout << char(input) << "|";
                outstream();
                entered += input;
            }

        }
        input = getch();
    }
}


int getPieceType(Piece* P)
{
    Pawn* Cp = dynamic_cast<Pawn*>(P);
    if (Cp != nullptr)
    {
        return 0;
    }
    Lance* Lp = dynamic_cast<Lance*>(P);
    if (Lp != nullptr)
    {
        return 1;
    }
    rook* Rp = dynamic_cast<rook*>(P);
    if (Rp != nullptr)
    {
        return 2;
    }
    silverGen* Sp = dynamic_cast<silverGen*>(P);
    if (Sp != nullptr)
    {
        return 3;
    }
    goldGen* Gp = dynamic_cast<goldGen*>(P);
    if (Gp != nullptr)
    {
        return 4;
    }
    bishop* Bp = dynamic_cast<bishop*>(P);
    if (Bp != nullptr)
    {
        return 5;
    }
    return 6;
}



void getRowColByMouse(int& r, int& c)
{
    while (!ismouseclick(WM_LBUTTONDOWN));

    getmouseclick(WM_LBUTTONDOWN, c, r);
}

void removeScreensFromEnd(string& content, int N)
{
    for (int i = 0; i < 16 * N;)
    {
        if (content[content.size() - 1] == '\n')
        {
            i++;
        }
        content.pop_back();
    }
    content.pop_back();
}



char selectAnOption()
{
    int r, c;
   
    while (true)
    {
        getRowColByMouse(r, c);
        if (c >= 300 && c <= 560)
        {
            if (r >= 250 && r <= 250 + bLen)
            {
                return 'n';
            }
            else if (r >= 350 && r <= 350 + bLen)
            {
                return 's';
            }
        }

    }
}

int APIENTRY WinMain
( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
//int main()
{
    char option;
    string filename;


    //loading all assets
    storeImage(h_circle, "extras/exp.gif");
    storeImage(pureblack1, "extras/pureblack1.gif");
    storeImage(gBox, "extras/gBox.gif");

    loadNormalPieces(blackNormal, whiteNormal);
    loadPromPieces(blackProm, whiteProm);



    while (true)
    {
        int fS = shogi::firstScreen();


        option = selectAnOption();

        if (option == 'n')
        {
            filename = "textfiles/newgame.txt";

            //emptying the replay.txt file
            ofstream fout("TextFiles/replay.txt", std::ios::ate);

        }
        else
        {
            string content;
            filename = "textfiles/saved.txt";

            //filling the replay.txt file with content from saved game's replay
            ifstream fin("textfiles/sReplay.txt");
            getline(fin, content, '\0');

            ////removing last screen from the content
            //removeScreensFromEnd(content, 1);
            
            ofstream fout("textFiles/replay.txt");
            fout << content;
        }


        shogi S(filename);
        closegraph(fS);


        mainW = initwindow(getmaxwidth(), getmaxheight(), "", 0, 0);

        S.play();
        closegraph(mainW);
    }
	return 0;
}





