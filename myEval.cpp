//
// Created by Mohye on 06/06/2020.
//
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include "myEval.h"
#include "myBST.h"
#include "myStack.h"
#include "regex"
#include <float.h>
#include "myHeap.h"
#define SMALLEST 2.22507385850720138e-308
Heap *myHeap= new Heap();
using namespace std;
BST myTree= BST();
void evaluateLine(string line)
{
    line=to_lower(line);
    line=removeSpaces(line.data());
    int lineTest=testLine(line);
    switch (lineTest){
        case 0: //Printing Operation
        {int LHS=testRegex(line);
            switch (LHS){

                case -1:
                {
                    line=line.substr(2);
                    Node *mynode=myTree.searchBST(line.data());
                    if(!mynode||mynode->key.empty())
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    } else
                    {
                        myTree.insert(line,mynode->value-1); //Decrement Thing print
                        cout << mynode->key << " = " << mynode->value << endl;
                        return;
                    }
                }
                case -3:
                {line=line.substr(0,line.size()-2);
                    Node *mynode=myTree.searchBST(line.data());
                    if(!mynode||mynode->key.empty())
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    } else
                    {
                        cout << mynode->key << " = " << mynode->value << endl;; //Print then decrement
                        myTree.insert(line,mynode->value-1);
                        return;
                    }}
                case 1:
                {
                    line=line.substr(2);
                    Node *mynode=myTree.searchBST(line.data());
                    if(!mynode||mynode->key.empty())
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    } else
                    {
                        myTree.insert(line,mynode->value+1);    //Increment Then Print
                        cout << mynode->key << " = " << mynode->value << endl;
                        return;
                    }}
                case 3:
                {
                    line=line.substr(0,line.size()-2);
                    Node *mynode=myTree.searchBST(line.data());
                    if(!mynode||mynode->key.empty())
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    } else
                    {
                        cout << mynode->key << " = " << mynode->value << endl; //Print Then Increment
                        myTree.insert(line,mynode->value+1);
                        return;
                    }
                }
                case 4:
                {
                    Node *mynode=myTree.searchBST(line.data());
                    if(!mynode||mynode->key.empty())
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    } else
                    cout << mynode->key << " = " << mynode->value << endl;
                    return;
                }
                default:
                {
                    if(!pairParn(line))
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    double result;
                    try {
                        result = evaluateRHS(line, myTree);
                    }catch (...)
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        return;
                    }
                    if(result!=DBL_MIN)
                        cout << result << endl;
                    return;
                }

            }}
        case 1: // Regular Operation
        {
            vector<string> linesplit=splitLineAt(line,'=');
            string lhs=linesplit[0];
            string rhs=linesplit[1];
            if(rhs.empty() || lhs.empty())
                {
                    cout << ">> " <<"Error at ^" << endl;
                    return;
                }
            int testRegexLHS=testRegex(lhs);
            switch (testRegexLHS)
            {
                case -2: // var-=
                {
                    rhs=lhs+rhs;
                    if(!pairParn(rhs))
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    lhs=lhs.substr(0,lhs.size()-1);
                    double result;
                    try {
                        result = evaluateRHS(rhs, myTree);

                    }catch (...)
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    myTree.insert(lhs,result);
                    break;

                }
                case 2: // var+=
                {
                    rhs=lhs+rhs;
                    if(!pairParn(rhs))
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    lhs=lhs.substr(0,lhs.size()-1);
                    double result;
                    try {
                        result = evaluateRHS(rhs, myTree);

                    }catch (...)
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    myTree.insert(lhs,result);
                    break;
                }
                case 4: // var =
                {
                    if(!pairParn(rhs))
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }

                    try {
                        double result = evaluateRHS(rhs, myTree);
                        if(result!=DBL_MIN)
                            myTree.insert(lhs,result);
                    }catch (...)
                    {
                        cout << ">> " <<"Error at ^" << endl;
                        break;
                    }
                    break;
                }
                default:
                    cout << ">> " << "Error at ^" << endl;
                    break;
            }

        }

    }
}
vector<string> splitLineAt(string line, char delm) {
    int del =line.find_first_of(delm);
    string lhs= line.substr(0,del);
    string rhs= line.substr(del+1);
    vector<string> cont;
    cont.emplace_back(lhs);
    cont.emplace_back(rhs);
    if(lhs==rhs)
    {
        cont.pop_back();
    }
    return cont;
}

int testRegex (string lhs)
{


    if(regex_match(lhs, regex("^\\-\\-[a-zA-Z_0-9]+")))
    {
        return -1; // Type 1 --variable
    } else if(regex_match(lhs, regex("[a-zA-Z_0-9]+\\-{1}$")))
    {
        return -2; // Type 2 variable- = ..
    }else if(regex_match(lhs, regex("[a-zA-Z_0-9]+\\-{2}$")))
    {
        return -3; // Type 3 variable-- no equal after
    }else if(regex_match(lhs, regex("^\\+\\+[a-zA-Z_0-9]+")))
    {
        return 1; // Type 1 ++variable
    } else if(regex_match(lhs, regex("[a-zA-Z_0-9]+\\+{1}$")))
    {
        return 2; // Type 2 variable+ = ..
    }else if(regex_match(lhs, regex("[a-zA-Z_0-9]+\\+{2}$")))
    {
        return 3; // Type 3 variable++ no equal after
    }else if( regex_match(lhs, regex("^[a-zA-z]+[a-zA-Z_0-9]*")))
    {
        return 4; // Type Regular Variable (x)
    }else if(  regex_match(lhs, regex("^[0-9]+\\.{0,1}[1-9]*")))
    {
        return 5; // Number
    }
    else
        return 0;
}

int testLine(string line)
{
    if(line.find_first_of("=")==string::npos)
    {
        return 0; // Priniting Operation
    }
    if(line.find_first_of("=")==line.find_last_of("=") )
    {
        return 1; // Regular Operation
    } else if (line.find_first_of("=")+1==line.find_last_of("=") )
    {
        return 2; // Boolean Operation
    } else
        return -1; // Invalid Equality
}
char *removeSpaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
bool pairParn(string &s)
{
    int r=0;
    int l=0;
    for (auto it = s.cbegin() ; it != s.cend(); ++it) {
        if(*it == '(')
            r++;
        if(*it==')')
            l++;
    }
    return r == l;
}
//bool checkRHS(string &s)
vector<string> splitAtOperators(string str)
{
    vector<string> parts;
    int lastOperatorindex=-1;
    for (int i=0;i<=str.size();i++)
    {
        if (str[i] == '('|| str[i] == ')' || str[i] == '+' || str[i] == '-'|| str[i] == '*'|| str[i] == '/'|| str[i] == '^')
        {
            char x = str[i];
            if(i!=lastOperatorindex+1) //Element at the start
            {
                if(lastOperatorindex==-1)
                {
                    string s=str.substr(lastOperatorindex+1,i+lastOperatorindex+1);
                    parts.push_back(s);
                } else
                {string s=str.substr(lastOperatorindex+1,i-lastOperatorindex-1);
                    parts.push_back(s);}
            }
            string s(1, str[i]);
            parts.push_back(s);
            lastOperatorindex=i;
        }
    }
    if(lastOperatorindex!=str.size()-1)
    {
        string s=str.substr(lastOperatorindex+1);
        parts.push_back(s);}

    return parts;
}
void inOrder()
{
    if(myTree.root==NULL)
    {
        cout << "No Variables Assigned" << endl;
        return;
    } else
    myTree.inorderTrav(myTree.root);
}
double evaluateRHS(string rhs,BST tree)
{
    int reg1=testRegex(rhs);
    if(reg1==1||reg1==-1||reg1==3||reg1==-3)
    {
        vector<string> v1=splitAtOperators(rhs);

        switch (reg1)
    {
        case 1: //++var
        {
            Node* inTree=tree.searchBST(v1[2].data());

            if(!inTree||inTree->key.empty())
            {
                throw "Error";
            } else
            {
                return ++inTree->value;
            }
        }
        case 3: //var++
        {
            Node* inTree=tree.searchBST(v1[0].data());

            if(!inTree||inTree->key.empty())
            {
                throw "Error";
            } else
            {
                return inTree->value++;
            }


            break;}
        case -1: //--var
        {
            Node* inTree=tree.searchBST(v1[2].data());

            if(!inTree||inTree->key.empty())
            {
                throw "Error";
            } else
            {
                return --inTree->value;
            }


            break;}
        case -3: //var--
        {

            Node* inTree=tree.searchBST(v1[0].data());

            if(!inTree||inTree->key.empty())
            {
                throw "Error";
            } else
            {
                return inTree->value--;
            }
    }
    }}
    vector<string> v=splitAtOperators(rhs);
double result = DBL_MIN;
    for(int i=0;i<v.size();i++)
    {
        int regTest=testRegex(v[i]);

           if(v[i].size()==1&&isOperator(v[i][0])) //Operator;
        {
            continue;
           } else if(regTest==4)
           {
               Node* inTree=tree.searchBST(v[i].data());

               if(!inTree||inTree->key.empty())
               {
                   throw "Error";
               } else
               {
                   v.at(i)=to_string(inTree->value);
               }

           }else if(regTest==5)
           {
               continue;
           } else
           {
               throw "Error";
           }

    }
    string RHSnew=accumulate(v.begin(), v.end(), string{});
    try {
        string post=infixToPostfix(RHSnew.data());
        result=evaluatePostfix(post.data());
        cout << "Infix Notation : " << RHSnew << endl;
        cout << "Postfix Notation : " << post << endl ;
        cout << "Result =  "<< result << endl ;

    }catch (...)
    {
        cout << ">> " << "Invalid Expression at ^" << endl;
        throw "Error";
    }
    return result;

}
string to_lower(string str)
{
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c){ return std::tolower(c); });
    return str;
}
void Heapsort()
{
    myHeap->BSTtoHeap(myTree);
}