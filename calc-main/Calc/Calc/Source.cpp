#include<iostream>
#include<string>
#include<vector>
#include "NumberObject.h"
using namespace std;
vector<NumberObject> variables;
void analyze_input(string input);
string analyze_formula(string input);
string convert_power(string input);
int isVariablesExist(string name);
int main() {
	string input;
	while (getline(cin, input)) {
		analyze_input(input);
	}
}
void analyze_input(string input) {
	while (input.find(" ") != -1) input.replace(input.find(" "), 1, "");//�h���ť�
	if (input.find_first_of("Set") == 0) {				//���O��Set
		string name;
		input.replace(0, 3, "");						//�h��Set
		if (input.find_first_of("Integer") == 0) {
			input.replace(0, 7, "");					//�h��Integer
			name.assign(input, 0, input.find("="));		//���oname
			input.erase(0, input.find("=") + 1);		//���o��
			string num = analyze_formula(input);		//�p���
			if (isVariablesExist(name) != -1) {			//�P�_�O�_�s�b���ܼ�
				variables[isVariablesExist(name)].SetNum(num);
			}
			else {
			Integer integer(name, num);					//�w�qInteger
			variables.push_back(integer);				//��J�ܼ�Vector
			}
			
		}
		else if(input.find_first_of("Decimal") == 0){
			input.replace(0, 7, "");					//�h��Decimal
			name.assign(input, 0, input.find("="));		//���oname
			input.erase(0, input.find("=") + 1);		//���o��
			string num = analyze_formula(input);		//�p���
			if (isVariablesExist(name) != -1) {			//�P�_�O�_�s�b���ܼ�
				variables[isVariablesExist(name)].SetNum(num);
			}
			else {
				Decimal decimal(name, num);					//�w�qInteger
				variables.push_back(decimal);				//��J�ܼ�Vector
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

//--------------------------------------------To analyze the formula
string analyze_formula(string input) {
	input = convert_power(input);
	//input = infix_to_postfix(input);
	return input;
}
string convert_power(string input) { //�NPower�ഫ���Ÿ��å[�W�A��
	while (input.find_last_of("Power") != -1) {
		int n = input.find_last_of("Power");
		int start,end,dot;
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
string infix_to_postfix(string input) {
	return "";
}
//--------------------------------------------

//translate the variable
int isVariablesExist(string name) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].name == name) return i;
	}
	return -1;
}