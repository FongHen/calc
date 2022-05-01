#include "NumberObject.h"
#include<vector>
#include<string>
using namespace std;
int intLen(string str);
int floatLen(string str);
int findDot(string str);
string delete_front(string str);
string delete_back(string str);
void muti_neg_one(NumberObject &num);
int compare(string str1, string str2);
NumberObject analyze_formula(string input);
NumberObject add(NumberObject a, NumberObject b);
NumberObject sub(NumberObject a, NumberObject b);
NumberObject muti(NumberObject a, NumberObject b);
NumberObject divi(NumberObject a, NumberObject b);
NumberObject int_divi(NumberObject a, NumberObject b);
NumberObject::NumberObject() {
	this->name = "";
	this->num = "0";
	type = INTEGER;
}
NumberObject::NumberObject(string num) {
	this->name = "";
	while (num[0] == '-') {
		muti_neg_one(*this);
		num.erase(0, 1);
	}
	this->num = num;
	if (findDot(num) != -1)this->type = DECIMAL;
	else type = INTEGER;
}
Integer::Integer() {
	this->name = "";
	this->num = "0";
	this->type = INTEGER;
}
Integer::Integer(string name, string num) {
	this->name = name;
	if (num.find(".") != -1) num.erase(num.find("."), num.length());
	this->num = num;
	this->type = INTEGER;
}
Decimal::Decimal() {
	this->name = "";
	this->num = "0";
	this->type = DECIMAL;
}
Decimal::Decimal(string name, string num) {
	this->name = name;
	this->num = num;
	this->type = DECIMAL;
}
void NumberObject::SetNum(string num) {
	while (num[0] == '-') {
		muti_neg_one(*this);
		num.erase(0, 1);
	}
	this->num = num;
	if (findDot(num) != -1)this->type = DECIMAL;
	else type = INTEGER;
}
void Integer::SetNum(string num) {
	while (num[0] == '-') {
		muti_neg_one(*this);
		num.erase(0, 1);
	}
	if (num.find(".") != -1) num.erase(num.find("."), num.length());
	this->num = num;
	this->type = INTEGER;
}
void Decimal::SetNum(string num) {
	while (num[0] == '-') {
		muti_neg_one(*this);
		num.erase(0, 1);
	}
	this->num = num;
	this->type = DECIMAL;
}
NumberObject NumberObject::operator+(NumberObject num) {
	NumberObject obj;
	if (this->sign == POSITIVE && num.sign == POSITIVE) {
		obj = add(*this, num);
	}
	else if (this->sign == POSITIVE && num.sign == NEGATIVE) {
		num.sign = POSITIVE;
		obj = sub(*this, num);
	}
	else if (this->sign == NEGATIVE && num.sign == POSITIVE) {
		this->sign = POSITIVE;
		obj = sub(num, *this);
	}
	else if (this->sign == NEGATIVE && num.sign == NEGATIVE) {
		
		obj= add(*this, num);
		obj.sign = NEGATIVE;
	}
	if (this->type == INTEGER && num.type == INTEGER) {
		obj.type = INTEGER;
	}
	else {
		obj.type = DECIMAL;
	}
	return obj;
}
NumberObject NumberObject::operator-(NumberObject num) {
	NumberObject obj;
	if (this->sign == POSITIVE && num.sign == POSITIVE) {
		obj = sub(*this, num);
	}
	else if (this->sign == POSITIVE && num.sign == NEGATIVE) {
		num.sign = POSITIVE;
		obj = add(*this, num);
	}
	else if (this->sign == NEGATIVE && num.sign == POSITIVE) {
		obj = add(*this, num);
		obj.sign = NEGATIVE;
	}
	else if (this->sign == NEGATIVE && num.sign == NEGATIVE) {
		num.sign = POSITIVE;
		obj = sub(num, *this);
	}
	if (this->type == INTEGER && num.type == INTEGER) {
		obj.type = INTEGER;
	}
	else {
		obj.type = DECIMAL;
	}
	return obj;
}
NumberObject NumberObject::operator*(NumberObject num) {
	NumberObject obj;
	if (this->sign == POSITIVE && num.sign == POSITIVE) {
		obj = muti(*this, num);
	}
	else if (this->sign == POSITIVE && num.sign == NEGATIVE) {
		obj = muti(*this, num);
		obj.sign = NEGATIVE;
		return obj;
	}
	else if (this->sign == NEGATIVE && num.sign == POSITIVE) {
		obj = muti(*this, num);
		obj.sign = NEGATIVE;
		return obj;
	}
	else if (this->sign == NEGATIVE && num.sign == NEGATIVE) {
		obj = muti(*this, num);
	}
	if (this->type == INTEGER && num.type == INTEGER) {
		obj.type = INTEGER;
	}
	else {
		obj.type = DECIMAL;
	}
	return obj;
}
NumberObject NumberObject::operator/(NumberObject num) {
	NumberObject obj;
	if (this->type == INTEGER && num.type == INTEGER) {
		obj = int_divi(*this, num);
		obj.type = INTEGER;
		if (this->sign == POSITIVE && num.sign == POSITIVE) {
			obj.sign = POSITIVE;
		}
		else if (this->sign == POSITIVE && num.sign == NEGATIVE) {
			obj.sign = NEGATIVE;
		}
		else if (this->sign == NEGATIVE && num.sign == POSITIVE) {
			obj.sign = NEGATIVE;
		}
		else if (this->sign == NEGATIVE && num.sign == NEGATIVE) {
			obj.sign = POSITIVE;
		}
	}
	else {
		obj= divi(*this, num);
		obj.type = DECIMAL;
		if (this->sign == POSITIVE && num.sign == POSITIVE) {
			obj.sign = POSITIVE;
		}
		else if (this->sign == POSITIVE && num.sign == NEGATIVE) {
			obj.sign = NEGATIVE;
		}
		else if (this->sign == NEGATIVE && num.sign == POSITIVE) {
			obj.sign = NEGATIVE;
		}
		else if (this->sign == NEGATIVE && num.sign == NEGATIVE) {
			obj.sign = POSITIVE;
		}
	}
	return obj;
}
NumberObject NumberObject::operator^(NumberObject num) {
	return *this;
}
bool NumberObject::operator==(NumberObject num) {
	if (this->num == num.num) {
		if (this->sign == num.sign) {
			return true;
		}
	}
	return false;
}
ostream& operator<<(ostream& os, NumberObject num) {
	if (num.num == "error") {
		return os;
	}
	else {
		if (num.type == DECIMAL) {
			if (findDot(num.num) == -1) {
				num.num = num.num + ".";
				for (int i = 0; i < 100; i++) num.num = num.num + "0";
			}
			else {
				int i = floatLen(num.num);
				for (i; i < 100; i++)num.num = num.num + "0";
			}
		}
		if (num.sign == POSITIVE) {
			os << num.num;
		}
		else {
			os << "-" << num.num;
		}
		return os;
	}
}
int intLen(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			return i + 1;
		}
	}
	return str.length();
}
int floatLen(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			return str.length() - i - 1;
		}
	}
	return 0;
}
int findDot(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			return i;
		}
	}
	return -1;
}
int compare(string str1, string str2) //单01-1
{
	if (str1.size() > str2.size())
		return 1;
	else if (str1.size() < str2.size())
		return -1;
	else return str1.compare(str2);     //璝单玥眖繷Юゑ耕
}
string delete_front(string str) {
	int i = 0;
	for (i = 0; i < str.length(); i++) {
		if (str[i] != '0' || str[i + 1] == '.')break;
	}
	if (str[0] == '0' && str[1] != '.') {
		str.erase(str.begin(), str.begin() + i);
	}
	return str;
}
string delete_back(string str) {
	int i = str.length() - 1;
	for (i = str.length() - 1; i > 0; i--) {
		if (str[i] == '.') {
			break;
		}
		else if (str[i] != '0') {
			i++;
			break;
		}
	}
	if (str[str.length() - 1] == '0' || str[str.length() - 1] == '.') {
		str.erase(str.begin() + i , str.end());
	}
	return str;
}
void muti_neg_one(NumberObject &num) {
	if (num.sign == POSITIVE) {
		num.sign = NEGATIVE;
	}
	else {
		num.sign = POSITIVE;
	}
}
NumberObject add(NumberObject a, NumberObject b) {
	string num;
	string num1 = a.num;
	string num2 = b.num;
	int carry = 0;
	int n, n1, n2, l;
	if (findDot(num1) == -1)num1.push_back('.');
	if (findDot(num2) == -1)num2.push_back('.');
	l = intLen(num1) - intLen(num2);
	if (l > 0) {
		for (int i = 0; i < l; i++) {
			//num2.insert(num2.front(), "0");
			num2 = "0" + num2;
		}
	}
	else {
		l = l * -1;
		for (int i = 0; i < l; i++) {
			//num1.insert(num1.front(), "0");
			num1 = "0" + num1;
		}
	}
	l = floatLen(num1) - floatLen(num2);
	if (l > 0) {
		for (int i = 0; i < l; i++) {
			num2.push_back('0');
		}
	}
	else {
		l = l * -1;
		for (int i = 0; i < l; i++) {
			num1.push_back('0');
		}
	}
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	num.resize(num1.length() + 1);
	for (int i = 0; i < num1.length(); i++) {
		num[i] = '0';
		if (num1[i]=='.') {
			num[i] = '.';
			continue;
		}
		else {
			n1 = num1[i] - '0';
			n2 = num2[i] - '0';
			n = (n1 + n2 +carry) % 10;
			carry = (n1 + n2 + carry) / 10;
			num[i] = ('0' + n);
		}
	}
	num[num1.length()] = ('0' + carry);
	reverse(num.begin(), num.end());
	num = delete_front(num);
	num = delete_back(num);
	NumberObject obj;
	obj.SetNum(num);
	return obj;
}
NumberObject sub(NumberObject a, NumberObject b) {
	string num;
	string num1 = a.num;
	string num2 = b.num;
	int carry = 0;
	int n, n1, n2, l;
	if (findDot(num1) == -1)num1.push_back('.');
	if (findDot(num2) == -1)num2.push_back('.');
	l = intLen(num1) - intLen(num2);
	if (l > 0) {
		for (int i = 0; i < l; i++) {
			//num2.insert(num2.front(), "0");
			num2 = "0" + num2;
		}
	}
	else {
		l = l * -1;
		for (int i = 0; i < l; i++) {
			//num1.insert(num1.front(), "0");
			num1 = "0" + num1;
		}
	}
	l = floatLen(num1) - floatLen(num2);
	if (l > 0) {
		for (int i = 0; i < l; i++) {
			num2.push_back('0');
		}
	}
	else {
		l = l * -1;
		for (int i = 0; i < l; i++) {
			num1.push_back('0');
		}
	}
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	num.resize(num1.length());
	for (int i = 0; i < num1.length(); i++) {
		num[i] = '0';
		if (num1[i] == '.') {
			num[i] = '.';
			continue;
		}
		else {
			n1 = num1[i] - '0';
			n2 = num2[i] - '0';
			if (n1 >= n2 + carry) {
				n = n1 - n2 - carry;
				carry = 0;
			}
			else {
				n = 10 + n1 - n2 - carry;
				carry = 1;
			}
			if (n == 10)n = 9;
			num[i] = ('0' + n);
		}
	}
	reverse(num.begin(), num.end());
	num = delete_front(num);
	num = delete_back(num);
	if (carry == 1) {
		NumberObject obj;
		obj = sub(b, a);
		muti_neg_one(obj);
		return obj;
	}
	else {
		NumberObject obj;
		obj.SetNum(num);
		return obj;
	}
}
NumberObject muti(NumberObject a, NumberObject b) {
	string num="";
	string num1 = a.num;
	string num2 = b.num;
	int dot1, dot2;
	int repair_zero = 0;
	vector<int> n;
	int carry = 0;
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	dot1 = findDot(num1);
	dot2 = findDot(num2);
	if (dot1 != -1) {
		repair_zero += dot1;
		num1.erase(num1.find_first_of('.'), 1);
	}
	if (dot2 != -1) {
		repair_zero += dot2;
		num2.erase(num2.find_first_of('.'), 1);
	}
	for (int i = 0; i < num1.length() + num2.length(); i++) {
		n.push_back(0);
	}
	for (int i = 0; i < num1.length(); i++) {
		for (int j = 0; j < num2.length(); j++) {
			int m;
			m = ((num1[i] - '0') * (num2[j] - '0'));
			n[i + j] = n[i + j] + m;
		}
	}
	for (int i = 0; i < n.size(); i++) {
		n[i] = n[i] + carry;
		carry = 0;
		if (n[i] > 9) {
			carry = n[i] / 10;
			n[i] = n[i] % 10;
		}
		num.push_back('0' + n[i]);
	}
	num.insert(repair_zero, ".");
	reverse(num.begin(), num.end());
	num = delete_front(num);
	num = delete_back(num);
	NumberObject obj;
	obj.SetNum(num);
	return obj;
}
NumberObject divi(NumberObject a, NumberObject b) {
	string num = "";
	string num1 = a.num;
	string num2 = b.num;
	int dot2 = findDot(num2);
	if (dot2 != -1) {
		int L = num2.size() - dot2 - 1;
		num2 = num2.erase(dot2, 1);//埃'.'
		num2 = delete_front(num2);
		NumberObject ten("10");
		for (int i = 0; i < L; i++) {
			a = muti(a, ten);
		}
	}
	num1 = a.num;
	string::size_type L1, L2;
	L1 = num1.size();
	L2 = num2.size();
	if (num2 == "0") {
		num = "ERROR!";
		return num;
	}
	else if (num1 == "0") {
		num = "0";
		return num;
	}
	string temp;
	temp = num1[0];
	//int dotInd = -1; //计翴竚
	int decCount = -1; //计材碭
	for (int i = 0; ; i++) {
		if (temp == "0" && i == L1) break; //俱埃
		else if (decCount == 100) break; //计100氨ゎ
		else if (temp == "0" && i >= L1) break; //Τ计
		if (i != 0) {
			//干0
			//セ计
			if (i >= L1 && num1.find('.') != -1) temp = temp + '0';
			//セ獶计
			else if (i == L1 && num1.find('.') == -1)temp = temp + '.';
			else if (i > L1 && num1.find('.') == -1) temp = temp + '0';
			//干计
			else temp = temp + num1[i];
		}
		temp.erase(0, temp.find_first_not_of('0')); //﹃い琩高材籔'0'ぃで皌じウ竚
		if (temp.empty())temp = "0";  //q.empty()讽︻true
		for (char ch = '9'; ch >= '0'; ch--) { //刚坝
			string str;
			str = str + ch;
			//笿计翴
			if (temp.find('.') != -1 && decCount == -1) {
				num = num + '.';
				temp.erase(temp.find('.'), 1);
				//dotInd = num.find('.');
				decCount = 0;
				break;
			}
			//猵
			if (compare(muti(num2, str).num, temp) <= 0) {
				if (num.find('.') != -1) {
					decCount += 1;
				}
				num = num + ch;

				temp = sub(temp, muti(num2, str)).num;

				break;
			}
		}
	}
	num = delete_front(num);
	return num;
}
NumberObject int_divi(NumberObject a, NumberObject b) {
	string num = "";
	string num1 = a.num;
	string num2 = b.num;

	string::size_type L1, L2;
	L1 = num1.size();
	L2 = num2.size();
	if (num2 == "0") {
		num = "ERROR!";
		return num;
	}
	else if (num1 == "0") {
		num = "0";
		return num;
	}
	string temp;
	//temp = num1[0];

	for (int i = 0; i < L1; i++) { //计彼
		//干计
		temp = temp + num1[i];
		temp.erase(0, temp.find_first_not_of('0')); //奔礚ノ0
		if (temp.empty()) temp = "0";  //temp= "0"
		for (char ch = '9'; ch >= '0'; ch--) { //刚坝
			string str;
			str = str + ch;
			//猵
			if (compare(muti(num2, str).num, temp) <= 0) {
				num = num + ch;
				temp = sub(temp, muti(num2, str)).num;
				break;
			}
		}
	}
	num = delete_front(num);
	return num;
}

Integer::Integer(const char* in) {
	string str = in;
	NumberObject n = analyze_formula(str);
	this->SetNum(n.num);
	this->sign = n.sign;
	this->type = INTEGER;
}
Decimal::Decimal(const char* in) {
	string str = in;
	NumberObject n = analyze_formula(str);
	this->num = in;
	this->SetNum(n.num);
	this->sign = n.sign;
	this->type = DECIMAL;
}
istream& operator>> (istream& is, Integer& num){
	string str;
	getline(is, str);
	NumberObject n = analyze_formula(str);
	num.SetNum(n.num);
	num.sign = n.sign;
	num.type = INTEGER;
	return is;
}
istream& operator>> (istream& is, Decimal& num) {
	string str;
	getline(is, str);
	NumberObject n = analyze_formula(str);
	num.SetNum(n.num);
	num.sign = n.sign;
	num.type = DECIMAL;
	return is;
}