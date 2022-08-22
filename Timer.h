#pragma once
#include<iostream>
using std::ostream;
using std::istream;
//timer class only for mins and seconds and for now only reverse timer
class Timer
{
	int min, sec;
public:
	Timer(int m=0, int s=0);
	void setTimer(int m = 0, int s = 0);
	bool operator==(const Timer& T)const;
	bool operator!=(const Timer& T)const;
	Timer operator-(const Timer& T)const;
	Timer& operator--();
	friend ostream& operator<<(ostream&out,const Timer& T);
	friend istream& operator >>(istream& in,Timer& T);
};

