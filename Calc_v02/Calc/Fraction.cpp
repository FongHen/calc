#include "Fraction.h"
#include<vector>
using namespace std;
void check_sign(Fraction& f);
void muti_neg_one(Fraction& f);
string delete_back(string str);
Fraction pow(Fraction a, Fraction b);
Fraction factorial(Fraction a);
int compare(string str1, string str2);
void Fraction::SetNum(NumberObject num) {
	this->numerator = num;
	if (this->numerator.sign == NEGATIVE) {
		this->sign = NEGATIVE;
		this->numerator.sign = POSITIVE;
	}
	NumberObject obj;
	obj.SetNum("1");
	this->denominator = obj;
}
Fraction Fraction::operator+(Fraction num) {
	if (this->denominator == num.denominator) {
		this->numerator = this->numerator + num.numerator;
	}
	else {
		this->numerator = (this->numerator * num.denominator) + (this->denominator * num.numerator);
		this->denominator = this->denominator * num.denominator;
	}
	check_sign(*this);
	return *this;
}
Fraction Fraction::operator-(Fraction num) {
	if (this->denominator == num.denominator) {
		this->numerator = this->numerator - num.numerator;
	}
	else {
		this->numerator = (this->numerator * num.denominator) - (this->denominator * num.numerator);
		this->denominator = this->denominator * num.denominator;
	}
	check_sign(*this);
	return *this;
}
Fraction Fraction::operator*(Fraction num) {
	this->numerator = this->numerator * num.numerator;
	this->denominator = this->denominator * num.denominator;
	check_sign(*this);
	return *this;
}
Fraction Fraction::operator/(Fraction num) {
	this->numerator = this->numerator * num.denominator;
	this->denominator = this->denominator * num.numerator;
	check_sign(*this);
	return *this;
}
Fraction Fraction::operator^(Fraction num) {
	return pow(*this, num);
}
Fraction Fraction::operator!() {
	return factorial(*this);
}
void check_sign(Fraction& f) {
	if (f.denominator.sign == NEGATIVE) {
		f.denominator.sign == POSITIVE;
		muti_neg_one(f);
	}
	if (f.numerator.sign == NEGATIVE) {
		f.numerator.sign == POSITIVE;
		muti_neg_one(f);
	}
}
void muti_neg_one(Fraction& f) {
	if (f.sign == POSITIVE) {
		f.sign = NEGATIVE;
	}
	else {
		f.sign = POSITIVE;
	}
}
Fraction pow(Fraction a, Fraction b) {
	NumberObject root = b.numerator / b.denominator;
	if (root.type == DECIMAL) {
		if (root.num == "0.5") {
			return a;
		}
		else {
			cout << "Root type Error!" << endl;
			return a;
		}
	}
	else {
		Fraction f;
		NumberObject one;
		NumberObject increase;
		NumberObject base;
		NumberObject out;
		one.SetNum("1");
		increase.SetNum("1");
		base = a.numerator / a.denominator;
		out = base;
		for (increase; compare(increase.num, root.num) == -1; increase = increase + one) {
			out = out * base;
		}
		f.SetNum(out);
		if (((root.num[root.num.length() - 1] - '0') % 2 == 1) && a.sign == NEGATIVE) {
			f.sign = NEGATIVE;
		}
		return f;
	}
}
Fraction factorial(Fraction a) {
	NumberObject num = a.numerator / a.denominator;
	num.num = delete_back(num.num);
	if (num.num.find(".") != -1) {
		cout << "Error!" << endl;
		return a;
	}
	else {
		Fraction f;
		NumberObject one;
		NumberObject increase;
		NumberObject out;
		one.SetNum("1");
		increase.SetNum("1");
		out.SetNum("1");
		for (increase; compare(increase.num, num.num) != 1; increase = increase + one) {
			out = out * increase;
		}
		f.SetNum(out);
		return f;
	}
}