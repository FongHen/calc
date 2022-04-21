#include "NumberObject.h"
using namespace std;
NumberObject::NumberObject() {
	this->name = "";
	this->num = "0";
}
NumberObject::NumberObject(string num) {
	this->name = "";
	this->num = num;
}
Integer::Integer() {
	this->name = "";
	this->num = "0";
}
Integer::Integer(string name, string num) {
	this->name = name;
	if (num[0] == '-') {
		num.erase(0, 1);
		this->sign = false;
	}
	if (num.find(".") != -1) num.erase(num.find("."), num.length());
	this->num = num;
}
Decimal::Decimal() {
	this->name = "";
	this->num = "0";
}
Decimal::Decimal(string name, string num) {
	this->name = name;
	if (num[0] == '-') {
		num.erase(0, 1);
		this->sign = false;
	}
	this->num = num;
}
void NumberObject::SetNum(string num) {
	this->num = num;
}
void Integer::SetNum(string num) {
	if (num.find(".") != -1) num.erase(num.find("."), num.length());
	this->num = num;
}