//
// Created by Mohye on 04/06/2020.
//
#include <stack>
#include <string>
using namespace std;
#pragma once
typedef union { // Union that holds either a Char or a float
    float fData;
    char cData;
} Item;
int isImportant(char a);
bool isOperator(char a);
char checktop(stack<Item>x);
string infixToPostfix(char * infix);
double evaluatePostfix(char *postfix);

