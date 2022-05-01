#include<iostream>
#include<string>
using namespace std;

#define N 50 //stack內運算子個數
#define OP 7 //運算子種類

int priority(char c); //回傳運算子優先權

//string infix_to_postfix(string infix); //中序轉後序

//------------------------------------------
/* stack 定義, 設定:僅存入運算子*/
char stackP[N];	// This is a global variable.
int top = -1;

void pushP(char item);   //將運算子放入堆疊
int popP();              //取出並移除 stack 最頂端的運算子
bool IsEmptyP(void);     //判斷是否為空堆疊
char top_dataP();        //僅回傳 stack 最頂端的運算子
//bool IsFull();          //判斷堆疊是否滿溢
//------------------------------------------


//------------------------------------------
/****** stack 定義, 設定:僅存入運算子******/
/*將運算子放入堆疊*/
void pushP(char item) {
	if (top >= N - 1) {
		cout << "Stack full!\n";
		exit(-1);
	}
	top++;
	stackP[top] = item;
}

/*取出並移除 stack 最頂端的運算子*/
int popP() {
	if (top == -1) {
		cout << "Stack empty!\n";
		exit(-1);
	}
	top--;
	return stackP[top + 1];
}

/*判斷是否為空堆疊*/
bool IsEmptyP(void) {
	if (top < 0) return true;
	else return false;
}

/*僅回傳 stack 最頂端的運算子*/
char top_dataP() {
	return stackP[top];
}

/*判斷堆疊是否滿溢*/
/*bool IsFull() {
	if (top >= N - 1)return true;
	else return false;
}
*/
//------------------------------------------



/*傳回運算子的優先序*/
int priority(char c) {
	switch (c) {
	case '(':
		return 5;
	case '!':
		return 4;
	case '^':
		return 3;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return -1;
	}
}

/*將中置式infix轉成後置式postfix*/
/*************NOTICE*************
()應對稱
沒有 +-(加減), -*(減乘) 連續的情況
*********************************/
string infix_to_postfix(string infix) {
	string postfix;
	int postL = infix.size() - count(infix.begin(), infix.end(), '(') * 2;
	postfix.resize(postL);
	int i = 0, j = -1;
	char x, y;
	x = infix[i];
	while (i < infix.size()) {
		switch (x) {
		case '(':
			pushP(x);
			break;
		case ')':
			y = top_dataP();
			while (!IsEmptyP()) {
				if (y == '(') {
					popP();
					y = top_dataP();
					break;
				}
				/*空格隔開*/
				postL++;
				j++;
				postfix.resize(postL);
				postfix[j] = ' ';
				/**/
				y = popP();
				j++;
				postfix[j] = y;
				y = top_dataP();
			}
			break;
		case '!':
			/*空格隔開*/
			postL++;
			j++;
			postfix.resize(postL);
			postfix[j] = ' ';
			/**/
			j++;
			postfix[j] = x;
			break;
		case '+':
			//判斷是否為正號，方法:找前一個字元，是的話skip
			if (i != 0) y = infix[i - 1];
			if (i == 0 || y == '(' || y == '+' || y == '-' || y == '*' || y == '/' || y == '^') break;
		case '-':
			//判斷是否為負號，方法:找前一個字元
			if (i != 0) y = infix[i - 1];
			if (i == 0 ||y == '(' || y == '+' || y == '-' || y == '*' || y == '/' || y == '^') {
				postL++;
				j++;
				postfix.resize(postL);
				postfix[j] = '-';
				break;
			}
		case '*':
		case '/':
			/*兩數字之間空格*/
			postL++;
			j++;
			postfix.resize(postL);
			postfix[j] = ' ';
			/**/
			y = top_dataP();
			while (priority(y) >= priority(x) && (y != '(')) {
				j++;
				postfix[j] = popP();
				y = top_dataP();
				/*符號輸出後以空格隔開*/
				postL++;
				j++;
				postfix.resize(postL);
				postfix[j] = ' ';
				/**/
			}
			pushP(x);
			break;
		case '^':
			/*兩數字之間空格*/
			postL++;
			j++;
			postfix.resize(postL);
			postfix[j] = ' ';
			/**/
			y = top_dataP();
			while (priority(y) > priority(x) && (y != '(')) { //次方由右至左, 故不==
				j++;
				postfix[j] = popP();
				y = top_dataP();
				/*符號輸出後以空格隔開*/
				postL++;
				j++;
				postfix.resize(postL);
				postfix[j] = ' ';
				/**/
			}
			pushP(x);
			break;
		default:
			j++;
			postfix[j] = x;
			break;
		}
		i++;
		x = infix[i];
	}
	while (!IsEmptyP()) {
		x = popP();
		if (x == '(') continue;
		/*空格隔開*/
		postL++;
		j++;
		postfix.resize(postL);
		postfix[j] = ' ';
		/**/
		j++;
		postfix[j] = x;
	}
	j++;
	postfix[j] = '\0';

	return postfix;
}