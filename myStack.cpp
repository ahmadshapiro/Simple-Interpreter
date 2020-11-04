//
// Created by Mohye on 04/06/2020.
//
#include "myStack.h"
#include "myEval.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stack>
#include <cstring>
#include <math.h>
using namespace std; //to ease the use of the function with out writing std , ex std::cout <<
int isImportant(char a) {  //to check the importance of an operator while changing from infix notation ro postfix notation using stacks
    if (a == '+' || a == '-')
        return 1;
    else if (a == '*' || a == '/')
        return 2;
    else if (a == '^')
        return 3;
    else if (a == '(')
        return 4;
    else if (a == ')')
        return 0;
    else
        return -1;


}
bool isOperator(char a) { // function returns bool : Char is operator ? true(1) : false(0)
    if (
            (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')' || a == '^'))
        return 1;
    else
        return 0;
}
char checktop(stack<Item>x)
{
    /*Since the stack top function returns null
 * if the stack is empty we need it to return false/0
 * to use it in comparison inside infixToPostfix function since the
 * we cannot compare null values */

    if(x.empty())
        return 0;
    else
        return x.top().cData;
}
string infixToPostfix(char * infix) {
    char infixcopy[strlen(infix)]; //making a copy of the passed infix notation ( parameter ) step 1
    string postfix=""; // initializing empty string for the postfix;
    strcpy(infixcopy, infix); //finalizing step 1
    removeSpaces(infixcopy);
    stack<Item> action; // initializing a stack the holds a data type of item to use it in the function
    char x; // general use character for slicing
    int i=0; // iterator to access each element in the infix string
    x = infixcopy[i]; // assigning the first character in the postfix to the general use variable X
    int closeoffer=0;
    int openoffer=0;
    while (x != NULL) {
        // while X is not null , in other words till we reach the last char in the infix string
        if(x=='(')
        {
            openoffer++;
        }
        if(x==' ')
        {
            x = infixcopy[++i]; // we shouldn't care for any extra Intending
            continue;
        }if(!action.empty())
        {
        if(((x=='+'&&action.top().cData=='-')||(x=='-'&&action.top().cData=='+'))&&(isOperator(infixcopy[i-1]))&&infixcopy[i-1]!=')')// Like 3-+2 = 3-2 or 3+-2 = 3-2
        {
            action.top().cData='-';
            x = infixcopy[++i];
            continue;
        } else if(x=='-'&&action.top().cData=='-'&&infixcopy[i+1]!='-')//like 3--2=3+2
        {
            {action.top().cData='+';
            closeoffer=0;
            }
            x = infixcopy[++i];
            continue;
        }
        if((isOperator(infixcopy[i-1])== 1)&& infixcopy[i-1]!=')'&& infixcopy[i+1]=='-' && x=='-')
            {
                i=i+2;
                x=infixcopy[i];
                continue;
            }
        }
        if (isOperator(x) == 1) { // checking if the X is operator
            if((i==0 || isOperator(infixcopy[i-1]) == 1) && x=='-' && !isOperator(infixcopy[i+1]) && infixcopy[i-1]!= ')' ) // for handling negative numbers
                /*
                 * if the first char is negative like in -3 + 2 for example
                 * or the previous element is an operator like this case 3 + -2 which will be the only cases to have
                 * negative numbers not a minus (-) operator
                 */
            {postfix+=x; /*
                 * if the condition is true we append the negative number notation to the postfix string
                 * and then complete the iteration assigning X to the next element in the infix string to process
                 */
                x = infixcopy[++i];
                continue;
            }
            // The condition is false and it's not a negative number then we proceed to the regular function
            Item trial; // making an item object called trial to push to the stack
            trial.cData = x; // assigning X to the cData in the trial Item
            if (isImportant(trial.cData) == 0) {
                /*
                 * Checking if X is a closing bracket ')' to pop out every operator
                 * in the stack TILL we reach X's couple ( opening bracket '(' )
                 * which applying the mathematical rule of operation priority
                 * that prioritize operations inside bracket first
                 */
                closeoffer++;
                if(openoffer==0)
                {
                    throw "Error";
                }
                int popped=0;
                while (isImportant(checktop(action)) != 4) {
                    char z = action.top().cData;
                    action.pop();
                    popped++;
                    postfix+=z;
                    postfix+=" "; // we append a space before and after operators to easily evaluate the resulting postfix notation
                }
                if(popped!=0||openoffer>=closeoffer)
                {
                    action.pop();
                }
                openoffer--;
                closeoffer--;
                // Condition is true , job is done, proceed to next character in the infix
                x = infixcopy[++i];
                continue;
            }
            // Condition is false and X isn't a closing bracket
            /*
             * also according to priority
             * while evaluating the expression we cannot push
             * a lowest or equal priority operator of the last operator we pushed in the stack ( TOP )
             * (as the stack ADT works with LIFO style which will result in doing low priority operation before the
             * high ones)
             * UNLESS the top was a opening bracket '(' , else we should pop everything out and
             * append it to the postfix
             */
            while ((isImportant(trial.cData) <= isImportant(checktop(action))) && (checktop(action) != '(')) {
                char m = action.top().cData;
                action.pop();
                postfix+=m;
                postfix+=" ";
            }
            // else we push the operator to the stack and then proceed
            action.push(trial);
            x = infixcopy[++i];
            continue;

        } else { // This the evaluation of operator , so if the char is an operand we should append it to the postfix String
            postfix+=x;
            /*
             * Here comes one of the coolest tricks, we should treat floats as a numbers ( no spaces between thier digits and the floating point
             * So , let's take 3.134 as an example here
             * 1- the first condition we're testing if the upcoming char in the infix is a floating point or not, if yes we shouldn't append a space
             * 2- if this variable is dot so common sense the rest is the digits of the floating number
             * 3- all of this must satisfy that next char we're testing it's an operator or and empty space , expression doesn't care if extra intending!
             */
            if((infixcopy[i+1]=='.') || (x=='.') || (postfix.back()=='.' && !isOperator(infixcopy[i+1])) || ((infixcopy[i+1]!=' ') && !isOperator(infixcopy[i+1])))
            {
                if(infixcopy[i+1]==NULL) // if it's the last number we should also add a space for evaluating
                    postfix+=" ";

            } else
            {
                postfix+=" "; // either wise we add a space
            }
        }
        if(isdigit(x)&&isalpha(infixcopy[i+1])) // for solving linear equations if the input is 3x we substitute it in the postfix with 3 x *
        {
            postfix+=" ";
            x='*';
            continue;
        }
        x = infixcopy[++i]; // else we proceed
    }
    while (! action.empty()) {
        // emptying out the stack to complete out postfix notation
        char z = action.top().cData;
        action.pop();
        postfix+=z;
        postfix+=" ";
    }
    return postfix;

}
double evaluatePostfix(char *pos) {
    // function is already implemented as the same in the stacks assignment
    char postfix[strlen(pos)];
    strcpy(postfix, pos);
    stack<Item> evaluation; // we make a stack for evaluating the postfix notation
    char *z; // char for iterating
    z = strtok(postfix, " "); // splitting at the space
    while (z!=NULL)
    {
        if(isOperator(z[0])!=1 || strlen(z)>1) // if it's not an operator or length more than 1 (operand)
        {
            Item value;
            value.fData=strtof(z, NULL); // we cast to float
            evaluation.push(value);// and then push to stack for further operation
            z = strtok(NULL, " "); // proceeding to the next char

        } else
            // else it's an operator
        {
            float x=evaluation.top().fData; // popping the last 2 entered floar numbers in the stack  ( operands of this specific operator)
            evaluation.pop();
            if(evaluation.empty()&&z[0]=='-') //(-(2+3)) 2 3 + - -> ( 5 - )
            {
                Item k;
                k.fData=x*-1;
                evaluation.push(k);
            } else if(evaluation.empty()&&z[0]=='+') //(-(2+3)) 2 3 + - -> ( 5 - )
            {
                Item k;
                k.fData=x;
                evaluation.push(k);
            }else
            {
                if(evaluation.empty())
                {
                    throw "Error!";
                }
            float y=evaluation.top().fData;
            evaluation.pop();
            Item op;
            op.fData=(z[0]=='+')?(x+y):((z[0]=='-')?(y-x):((z[0]=='*')?(x*y):((z[0]=='/')?(y/x):((z[0]=='^')?(powf(y,x)):0)))); // doing the opearion
            evaluation.push(op);} // pushing to stack again
            z = strtok(NULL, " "); // proceeding to next char in postfix
        }
    }
    strcpy(postfix,"");
    return evaluation.top().fData; // returning the most top element ( result )

}

