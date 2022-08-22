#include "Timer.h"
#include<iomanip>
Timer::Timer(int m, int s)
{
	min = m, sec = s;
}

void Timer::setTimer(int m, int s)
{
	min = m, sec = s;
}

bool Timer::operator==(const Timer& T)const
{
	return min == T.min && sec == T.sec;
}

bool Timer::operator!=(const Timer& T) const
{
	return !(*this == T);
}

Timer Timer::operator-(const Timer& T)const
{

	Timer R;
	R.sec = this->sec - T.sec;
	int carry = 0;
	if (R.sec < 0)
	{
		R.sec += 60;
		carry = 1;
	}
	R.min = this->min - T.min - carry;
	return R;
}

Timer& Timer::operator--()
{
	Timer T{ 0,1 };
	*this = *this - T;
	return *this;
}

ostream& operator<<(ostream& out, const Timer& T)
{
	out << std::setw(2) << std::setfill('0')  << T.min <<":"<< std::setw(2) << std::setfill('0') << T.sec;
	return out;
}

istream& operator >>(istream& in,Timer& T)
{
	in >> T.min;
	in.ignore();
	in >> T.sec;
	return in;
}
