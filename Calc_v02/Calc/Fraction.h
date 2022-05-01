#pragma once
#include<iostream>
#include"NumberObject.h"
using namespace std;
class Fraction {
public:
	NumberObject numerator;//¤À¤l
	NumberObject denominator;//¤À¥À
	SIGN sign = POSITIVE;
	type type = INTEGER;
	void SetNum(NumberObject num);
	Fraction operator+(Fraction num);
	Fraction operator-(Fraction num);
	Fraction operator*(Fraction num);
	Fraction operator/(Fraction num);
	Fraction operator^(Fraction num);
	Fraction operator!();
};