//
// Created by Mohye on 06/06/2020.
//
#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <math.h>
#include <vector>
#include <algorithm>
#include "myBST.h"
using namespace std;

vector<string> splitLineAt(string line ,char delm);
int testLine(string line);
int testRegex (string lhs);
char *removeSpaces(char *str);
vector<string> splitAtOperators(string str);
bool pairParn(string &s);
double evaluateRHS(string rhs,BST tree);
void evaluateLine(string line);
void inOrder();
string to_lower(string str);
void Heapsort();