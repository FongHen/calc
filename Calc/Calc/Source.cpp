#include<iostream>
#include<string>
#include<vector>
#include "NumberObject.h"
using namespace std;
vector<NumberObject> variables;
void analyze_input(string input);
string analyze_formula(string input);
int isVariablesExist(string name);
int main() {
	string input;
	while (getline(cin, input)) {
		analyze_input(input);
	}
}
void analyze_input(string input) {
	while (input.find(" ") != -1) input.replace(input.find(" "), 1, "");
	if (input.find_first_of("Set") == 0) {				//指令為Set
		string name;
		input.replace(0, 3, "");						//去掉Set
		if (input.find_first_of("Integer") == 0) {
			input.replace(0, 7, "");					//去掉Integer
			name.assign(input, 0, input.find("="));		//取得name
			input.erase(0, input.find("=") + 1);		//取得值
			string num = analyze_formula(input);		//計算值
			if (isVariablesExist(name) != -1) {			//判斷是否存在此變數
				variables[isVariablesExist(name)].SetNum(num);
			}
			else {
			Integer integer(name, num);					//定義Integer
			variables.push_back(integer);				//放入變數Vector
			}
			
		}
		else if(input.find_first_of("Decimal") == 0){
			input.replace(0, 7, "");					//去掉Decimal
			name.assign(input, 0, input.find("="));		//取得name
			input.erase(0, input.find("=") + 1);		//取得值
			string num = analyze_formula(input);		//計算值
			if (isVariablesExist(name) != -1) {			//判斷是否存在此變數
				variables[isVariablesExist(name)].SetNum(num);
			}
			else {
				Decimal decimal(name, num);					//定義Integer
				variables.push_back(decimal);				//放入變數Vector
			}
		}
	}
	else if (input.find_first_of("=") != -1) {
		string name;
		name.assign(input, 0, input.find("="));
		input.erase(0, input.find("=") + 1);
		if (isVariablesExist(name) != -1) {
			string num;
			num = analyze_formula(input);
			variables[isVariablesExist(name)].SetNum(num);
		}
		else {
			cout << "Error! Variable doesn't exist!" << endl;
		}
	}
	else {
		string num = analyze_formula(input);
		cout << num << endl;
	}
}
string analyze_formula(string input) {
	return "Not YETT";
}
int isVariablesExist(string name) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].name == name) return i;
	}
	return -1;
}