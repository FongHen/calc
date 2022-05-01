#include<iostream>
#include<string>
using namespace std;

#define N 50 //stack���B��l�Ӽ�
#define OP 7 //�B��l����

int priority(char c); //�^�ǹB��l�u���v

//string infix_to_postfix(string infix); //��������

//------------------------------------------
/* stack �w�q, �]�w:�Ȧs�J�B��l*/
char stackP[N];	// This is a global variable.
int top = -1;

void pushP(char item);   //�N�B��l��J���|
int popP();              //���X�ò��� stack �̳��ݪ��B��l
bool IsEmptyP(void);     //�P�_�O�_���Ű��|
char top_dataP();        //�Ȧ^�� stack �̳��ݪ��B��l
//bool IsFull();          //�P�_���|�O�_����
//------------------------------------------


//------------------------------------------
/****** stack �w�q, �]�w:�Ȧs�J�B��l******/
/*�N�B��l��J���|*/
void pushP(char item) {
	if (top >= N - 1) {
		cout << "Stack full!\n";
		exit(-1);
	}
	top++;
	stackP[top] = item;
}

/*���X�ò��� stack �̳��ݪ��B��l*/
int popP() {
	if (top == -1) {
		cout << "Stack empty!\n";
		exit(-1);
	}
	top--;
	return stackP[top + 1];
}

/*�P�_�O�_���Ű��|*/
bool IsEmptyP(void) {
	if (top < 0) return true;
	else return false;
}

/*�Ȧ^�� stack �̳��ݪ��B��l*/
char top_dataP() {
	return stackP[top];
}

/*�P�_���|�O�_����*/
/*bool IsFull() {
	if (top >= N - 1)return true;
	else return false;
}
*/
//------------------------------------------



/*�Ǧ^�B��l���u����*/
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

/*�N���m��infix�ন��m��postfix*/
/*************NOTICE*************
()�����
�S�� +-(�[��), -*(�) �s�򪺱��p
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
				/*�Ů�j�}*/
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
			/*�Ů�j�}*/
			postL++;
			j++;
			postfix.resize(postL);
			postfix[j] = ' ';
			/**/
			j++;
			postfix[j] = x;
			break;
		case '+':
			//�P�_�O�_�������A��k:��e�@�Ӧr���A�O����skip
			if (i != 0) y = infix[i - 1];
			if (i == 0 || y == '(' || y == '+' || y == '-' || y == '*' || y == '/' || y == '^') break;
		case '-':
			//�P�_�O�_���t���A��k:��e�@�Ӧr��
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
			/*��Ʀr�����Ů�*/
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
				/*�Ÿ���X��H�Ů�j�}*/
				postL++;
				j++;
				postfix.resize(postL);
				postfix[j] = ' ';
				/**/
			}
			pushP(x);
			break;
		case '^':
			/*��Ʀr�����Ů�*/
			postL++;
			j++;
			postfix.resize(postL);
			postfix[j] = ' ';
			/**/
			y = top_dataP();
			while (priority(y) > priority(x) && (y != '(')) { //����ѥk�ܥ�, �G��==
				j++;
				postfix[j] = popP();
				y = top_dataP();
				/*�Ÿ���X��H�Ů�j�}*/
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
		/*�Ů�j�}*/
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