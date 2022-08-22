#pragma once
#include<iostream>
#include<vector>
#include"graphics.h"

extern LPPICTURE whiteNormal[8], whiteProm[6], blackNormal[8], blackProm[6], h_circle, pureblack1, gBox;
extern int mainW;//store the mainW in this

using std::cout; using std::cin; using std::endl; using std::string; using std::vector;
enum class Color{BLACK,WHITE=15};

void storeImage(LPPICTURE& P, const char* filename = '\0');//stores picture in an LPPICTURE data type
void printImage(LPPICTURE& pPicture, int left, int top, int right, int bottom);//displays pictures form LPPICTURE data type

constexpr auto bLen = 65; //box length;
constexpr auto iStart = 7;//push image five Pixels inside the box
constexpr auto iEnd = 58; //image len 58-7=51 and area= 51*51
constexpr auto wcpRow = 7; //white cap pieces row
constexpr auto bcpRow = 3; //black cap pieces row
constexpr auto cpCol = 10; //cap pieces col
constexpr auto GOLD_COLOR = 51956479;


