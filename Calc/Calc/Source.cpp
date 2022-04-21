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
string analyze_formula(string input) {
	return "Not YETT";
}
int isVariablesExist(string name) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].name == name) return i;
	}
	return -1;
}