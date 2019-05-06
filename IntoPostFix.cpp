#include <string>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '$':
		weight = 3;
		break;
	}
	return weight;
}
bool isNumber(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	else {
		return false;
	}
}
bool IsHigherPrecedence(char inputTop, char inputNext) {

	int topWeight = GetOperatorWeight(inputTop);
	int nextWeight = GetOperatorWeight(inputNext);

	return topWeight >= nextWeight ? true : false;

}
bool IsOperator(char input) {
	if ((input == '*') || input == '-' || input == '+'||input == '/') {
		return true;
	}
	else
		return false;
}
string InfixToPostfix(string input) {
	stack<char> stk;
	string postfix = "";

	for (int i = 0; i < input.length(); ++i) {
		if (isspace(input.at(i)) != 0) {
			continue;
		}
		else if (input.at(i) == '(') {
			stk.push(input.at(i));
		}
		else if (isNumber(input.at(i))) {
			postfix.push_back(input.at(i));
		}
		else if (IsOperator(input.at(i))) {
			while (!(stk.empty()) && (stk.top() != '(') && IsHigherPrecedence(stk.top(), input.at(i))){
				postfix.push_back(stk.top());
				stk.pop();
			}
			stk.push(input.at(i));
		}
		else if (input.at(i) == ')') {
			postfix.push_back(stk.top());
			stk.pop();
			while (stk.top() != '(') {
				postfix.push_back(stk.top());
				stk.pop();
			}
			stk.pop();
		}
	}
	while (!stk.empty()) {
		postfix.push_back(stk.top());
		stk.pop();
	}
	return postfix;
}
double EvaluatePostExpression(string input) {
	stack<double> stk;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == ' ') {
			continue;
		}
		else if (isNumber(input[i])) {
			double operand = (double)(input.at(i) - '0');
			stk.push(operand);
		}
		else {
			double rightOperand = stk.top();
			stk.pop();
			double leftOperand = stk.top();
			stk.pop();
			if (input[i] == '*') {
				stk.push(leftOperand * rightOperand);

			}
			if (input[i] == '-') {
				stk.push(leftOperand - rightOperand);
			}
			if (input[i] == '+') {
				stk.push(leftOperand + rightOperand);
			}
			if (input[i] == '/') {
				stk.push(leftOperand / rightOperand);
			}


		}
	}
	return stk.top();
}
int main() {
	char dataFileName[] = "data.txt";

	ifstream fileData;
	fileData.open(dataFileName, 0);
	if (fileData.good() == false)
	{
		cout << "ERROR: can't open data file: " << dataFileName << endl;

		cout << endl << "Press the [Enter] key to quit...";
		cin.get();
		return -1;
	}
	while (fileData.eof() == false)
	{
		string infix;

		for (int i = 0; i < 14; ++i) {

			getline(fileData, infix, '\n');
			if (fileData.good() == false)
				break;
			cout << "\ninfix: " << infix << endl;
			cout << "postfix: " << InfixToPostfix(infix);
			cout << "\nanswer: " << EvaluatePostExpression(InfixToPostfix(infix)) << endl;



		}
	}
	fileData.close();
	getchar();
}