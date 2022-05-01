#pragma once
#include<iostream>
using namespace std;
enum SIGN
{
	POSITIVE,
	NEGATIVE
};
enum type
{
	INTEGER,
	DECIMAL
};
class NumberObject {
public:
	string num;
	string name;
	SIGN sign = POSITIVE;
	type type;
	NumberObject();
	NumberObject(string num);
	void SetNum(string num);
	NumberObject operator+(NumberObject num);
	NumberObject operator-(NumberObject num);
	NumberObject operator*(NumberObject num);
	NumberObject operator/(NumberObject num);
	NumberObject operator^(NumberObject num);
	bool operator==(NumberObject num);
	friend ostream& operator<<(ostream& os, NumberObject num);
};
class Integer: public NumberObject {
public:
	Integer();
	Integer(const char* in);
	Integer(string name, string num);
	void SetNum(string num);
	friend istream& operator>> (istream& is, Integer& num);
};
class Decimal: public NumberObject {
public:
	Decimal();
	Decimal(const char* in);
	Decimal(string name, string num);
	void SetNum(string num);
	friend istream& operator>> (istream& is, Decimal& num);
};
