#pragma once
#include<iostream>
using namespace std;
class NumberObject {
public:
	string num;
	string name;
	bool sign = true;
	NumberObject();
	NumberObject(string num);
	void SetNum(string num);
};
class Integer: public NumberObject {
public:
	Integer();
	Integer(string name, string num);
	void SetNum(string num);
};
class Decimal: public NumberObject {
public:
	Decimal();
	Decimal(string name, string num);
};