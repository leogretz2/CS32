#include "Set.h"
#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;


void InToPost(string infix, string& postfix);
int evaluate(string infix, const Set& trueValues, const Set& falseValues,
	string& postfix, bool& result);
int precedence(char ch);
bool pCheck(string infix);
bool isValid(string infix);
int setsFit(string infix, const Set& trueValues, const Set& falseValues);
bool solve(string postfix, const Set& trueValues, const Set& falseValues);


int evaluate(string infix, const Set& trueValues, const Set& falseValues,
	string& postfix, bool& result)
{
	if (!isValid(infix))
		return 1;
	InToPost(infix, postfix);
	switch (setsFit(postfix, trueValues, falseValues)) {
		case 0:
			result = solve(postfix, trueValues, falseValues);
			return 0;
		case 2: 
			return 2;
		case 3: 
			return 3;
		default:
			break;
	}
	return 1;
}

void InToPost(string infix, string& postfix) {
	postfix = "";
	stack<char> operatorStack;
	for (int i = 0; i < infix.size(); i++) {
		char ch = infix[i];
		if (islower(ch)) {
			postfix += ch;
			continue;
		}
		switch (ch) {
			case '(':
				operatorStack.push(ch);
				break;
			case ')':
				while (operatorStack.top() != '(') {
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.pop();
				break;
			case '&':
			case '|':
				while (!operatorStack.empty() && operatorStack.top() != '(' && 
					precedence(ch) <= precedence(operatorStack.top())) {
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.push(ch);
				break;
			case '!':
				while (!operatorStack.empty() && operatorStack.top() != '(' &&
					precedence(ch) < precedence(operatorStack.top())) {
					postfix += operatorStack.top();
					operatorStack.pop();
				}
				operatorStack.push(ch);
				break;
			default:
				break;
		}
	}
	while (!operatorStack.empty()) {
		postfix += operatorStack.top();
		operatorStack.pop();
	}
}

int precedence(char ch) {
	switch (ch) {
		case '!':
			return 3;
		case '&':
			return 2;
		case '|': 
			return 1;
	}
	return 0;
}

bool pCheck(string infix) {
	int count = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(')
			count++;
		if (infix[i] == ')')
			count--;
		if (count < 0)
			return false;
	}
	if (count == 0)
		return true;
	return false;
}

bool isValid(string infix) {
	string temp;
	for (int i = 0; i < infix.size(); i++)
		if (!isspace(infix[i]))
			temp += infix[i];
	if (!pCheck(temp))
		return false;
	if ((temp.size() == 0) || (temp.size() == 1 && !islower(temp[0])))
		return false;
	if (!temp[0] == '(' && !temp[0] == '!' && !islower(temp[0]))
		return false;
	if (temp[temp.size() - 1] == '(' || temp[temp.size() - 1] == '|' ||
		temp[temp.size() - 1] == '&' || temp[temp.size() - 1] == '!')
		return false;
	for (int i = 1; i < temp.size(); i++) {
		char ch = temp[i];
		char prev = temp[i - 1];
		if (!(ch == '(') && !(ch == ')') && !(ch == '!') && !(ch == '&') && !(ch == '|') &&
			!(islower(ch)) && !(isspace(ch)))
			return false;
		if (islower(ch))
			if (prev == ')' || isalpha(prev))
				return false;
		switch (ch) {
		case '&':
			if (prev == '&' || prev == '!' || prev == '|' || prev == '(')
				return false;
			break;
		case '|':
			if (prev == '&' || prev == '!' || prev == '|' || prev == '(')
				return false;
			break;
		case ')':
			if (prev == '&' || prev == '!' || prev == '|' || prev == '(')
				return false;
			break;
		case '(':
			if (isalpha(prev))
				return false;
			break;
		case '!':
			if (prev == ')' || islower(prev))
				return false;
			break;
		}
	}
	return true;
}

int setsFit(string postfix, const Set& trueValues, const Set& falseValues) {
	for (int i = 0; i < postfix.size(); i++) {
		char ch = postfix[i];
		if (islower(ch)) {
			if (!trueValues.contains(ch) && !falseValues.contains(ch))
				return 2;
			if (trueValues.contains(ch) && falseValues.contains(ch))
				return 3;
		}
	}
	return 0;
}

bool solve(string postfix, const Set& trueValues, const Set& falseValues) {
	stack<bool> operandStack;
	for (int i = 0; i < postfix.size(); i++) {
		char ch = postfix[i];
		if (islower(ch)) {
			if (trueValues.contains(ch)) {
				operandStack.push(1);
			}
			else {
				operandStack.push(0);
			}
		}
		else if (ch == '!') {
			bool answer;
			bool operand = operandStack.top();
			operandStack.pop();
			answer = !operand;
			operandStack.push(answer);
		} 
		else {
			bool answer;
			bool operand2 = operandStack.top();
			operandStack.pop();
			bool operand1 = operandStack.top();
			operandStack.pop();
			switch (ch) {
				case '&':
					answer = operand1 && operand2;
					break;
				case '|':
					answer = operand1 || operand2;
					break;
			}
			operandStack.push(answer);
		}
	}
	return operandStack.top();
}


//int main() {
//	string infix = "a & !(s | u & c | n) | !!!(s&u&n)";
//	string postfix = "bleh";
//
//	/*u                          evaluates to true
//		u&c&l&a & !(u&s&c)         evalates to true
//		(n)evaluates to false
//		a&(s)evaluates to false
//		a & !s                     evaluates to true
//		!(n | u)                     evaluates to false
//		!n | u                       evaluates to true
//		a | n & n                      evaluates to true
//		a & !(s | u & c | n) | !!!(s&u&n)    evaluates to true*/
//
//	Set trues;
//	Set falses;
//	string trueChars = "ucla";
//	string falseChars = "nsx";
//	for (int k = 0; k < trueChars.size(); k++)
//		trues.insert(trueChars[k]);
//	for (int k = 0; k < falseChars.size(); k++)
//		falses.insert(falseChars[k]);
//
//	bool result = false;
//
//	cout << evaluate(infix, trues, falses, postfix, result) << ":  ";
//	if (result)
//		cout << 1 << endl;
//	else
//		cout << 0 << endl;
//	//InToPost(infix, postfix);
//	/*for (int i = 0; i < postfix.size(); i++) {
//		cout << postfix[i];
//	}
//	cout << endl;*/
//}
//