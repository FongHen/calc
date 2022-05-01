#include<iostream>
#include<string>
#include<vector>
#include <sstream>
#include <stack>
#include <cctype>
#include "NumberObject.h"
#include"Fraction.h"
using namespace std;
vector<NumberObject> variables;
void analyze_input(string input);
NumberObject analyze_formula(string input);
string convert_power(string input);
string infix_to_postfix(string input);
NumberObject pofixComput(string  input);
int isVariablesExist(string name);
bool isSymbol(char c);
bool input_check(string str);
int main() {
	string input;
	/*測試用程式
	Integer i = "123";
	Decimal d = "123.3";
	Integer i;
	Decimal d;
	cin >> i >> d;
	cout << i << endl << d << endl;
	vector<NumberObject*> nums;
	nums.push_back(&i);
	nums.push_back(&d);
	for (const auto& num : nums) cout << *num << endl;
	*/

	while (getline(cin, input)) {
		analyze_input(input);
	}
}
void analyze_input(string input) {
	while (input.find(" ") != -1) input.replace(input.find(" "), 1, "");//去除空白
	//Set
	if (input.find_first_of("Set") == 0) {				//指令為Set
		string name;
		int pos;
		input.replace(0, 3, "");						//去掉Set
		if (input.find_first_of("Integer") == 0) {
			input.replace(0, 7, "");					//去掉Integer
			name.assign(input, 0, input.find("="));		//取得name
			input.erase(0, input.find("=") + 1);		//取得值
			NumberObject num = analyze_formula(input);	//計算值
			pos = isVariablesExist(name);
			if (pos != -1) {							//判斷是否存在此變數

				variables[pos] = num;
				variables[pos].name = name;
			}
			else {
				Integer integer;
				integer.name = name;
				integer.SetNum(num.num);
				integer.sign = num.sign;
				variables.push_back(integer);				//放入變數Vector
			}
		}
		else if(input.find_first_of("Decimal") == 0){
			input.replace(0, 7, "");					//去掉Decimal
			name.assign(input, 0, input.find("="));		//取得name
			input.erase(0, input.find("=") + 1);		//取得值
			NumberObject num = analyze_formula(input);		//計算值
			pos = isVariablesExist(name);
			if (isVariablesExist(name) != -1) {			//判斷是否存在此變數
				variables[pos] = num;
				variables[pos].name = name;
			}
			else {
				Decimal decimal;
				decimal.name = name;
				decimal.SetNum(num.num);
				decimal.sign = num.sign;
				variables.push_back(decimal);
			}
		}
	}
	//Set Integer or Decimal
	else if (input.find_first_of("=") != -1) {
		string name;
		int pos;
		name.assign(input, 0, input.find("="));
		input.erase(0, input.find("=") + 1);
		pos = isVariablesExist(name);
		if (pos != -1) {
			NumberObject num;
			num = analyze_formula(input);
			num.name = name;
			num.type = variables[pos].type;
			variables[pos]=num;
		}
		else {
			cout << "Error! Variable doesn't exist!" << endl;
		}
	}
	//Calculate
	else {
		NumberObject num;
		num = analyze_formula(input);
		cout << num << endl;
	}
}

//--------------------------------------------To analyze the formula
NumberObject analyze_formula(string input) {
	NumberObject out;
	input = convert_power(input);
	input = infix_to_postfix(input); 
	cout << input << endl;
	out = pofixComput(input);
	return out;
}
string convert_power(string input) { //將Power轉換成符號並加上括號
	while (input.find_last_of("Power") != std::string::npos) {
		int n = input.find_last_of("Power");
		int start = 0, end = 0, dot = 0;
		input.erase(n - 4, 5);
		start = n - 4;
		for (int i = n - 3; i < input.size(); i++) {
			if (input[i] == ',') {
				dot = i;
				break;
			}
		}
		int tmp = 0;
		for (int i = dot; i < input.size(); i++) {
			if (input[i] == '(') {
				tmp++;
			}
			else if (input[i] == ')') {
				if (tmp == 0) {
					end = i;
					break;
				}
				else {
					tmp--;
				}
			}
		}
		input.insert(end, ")");
		input.insert(dot + 1, "(");
		input[dot] = '^';
		input.insert(dot, ")");
		input.insert(start, "(");
	}
	return input;
}
NumberObject pofixComput(string input) {
	stack<Fraction> postFixStack;
	istringstream in = istringstream(input);
	string str;
	while (in >> str)
	{
		if (isSymbol(str[0]) && str[1] == '\0') {
			str.resize(1);
		}
		if (str == "+") {
			Fraction num2 = postFixStack.top();
			postFixStack.pop();
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(num1 + num2);
		}
		else if (str == "-") {
			Fraction num2 = postFixStack.top();
			postFixStack.pop();
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(num1 - num2);
		}
		else if (str == "*") {
			Fraction num2 = postFixStack.top();
			postFixStack.pop();
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(num1 * num2);
		}
		else if (str == "/") {
			Fraction num2 = postFixStack.top();
			postFixStack.pop();
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(num1 / num2);
		}
		else if (str == "^") {
			Fraction num2 = postFixStack.top();
			postFixStack.pop();
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(num1 ^ num2);
		}
		else if (str == "!") {
			Fraction num1 = postFixStack.top();
			postFixStack.pop();
			postFixStack.push(!num1);
		}
		else if (str == ""){

		}
		else {
			if (isVariablesExist(str) != -1) {
				int i;
				for (i = 0; i < variables.size(); i++) {
					if (variables[i].name == str) break;
				}
				Fraction f;
				f.SetNum(variables[i]);
				postFixStack.push(f);
			}
			else {
				if (input_check(str)) {
					NumberObject num;
					num.SetNum(str);
					Fraction f;
					f.SetNum(num);
					postFixStack.push(f);
				}
				else {
					NumberObject num;
					cout << "Error!Input Wrong!" << endl;
					num.SetNum("error");
					return num;
				}
				
			}
		}
	}
	NumberObject obj;
	obj = postFixStack.top().numerator / postFixStack.top().denominator;
	obj.sign = postFixStack.top().sign;
	return obj;
}
//--------------------------------------------

//translate the variable
int isVariablesExist(string name) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].name == name) return i;
	}
	return -1;
}
bool isSymbol(char c) {
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '!':
	case '^':
		return true;
	default:
		return false;
	}
}
bool input_check(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (!isSymbol(str[i]) && !isdigit(str[i])&&str[i]!='.') {
			return false;
		}
	}
	return true;
}