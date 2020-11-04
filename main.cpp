#include <iostream>
#include <string>
#include <string.h>
#include <stack>
#include <cstring>
#include <math.h>
#include <vector>
#include <algorithm>
#include "myStack.h"
#include "myBST.h"
#include "myHeap.h"
#include "myEval.h"
#include <regex>
#include <exception>
#include <fstream>
#include <conio.h>

using namespace std;
int flag=1;
void ClearScreen()
{
    cout << string( 100, '\n' );
}
void fileRead()
{
    ClearScreen();
    cout << "Reading from File" << endl;
    cout << "============================\n" << endl;
    while (true)
    {
    cout << "Please Enter File Name (And Make Sure it's in the cmake-build-debug Folder) also ends with .txt" << endl;
    string fileName;
    cin >> fileName;
    if(fileName.find(".txt")==string::npos)
    {cout << "Invalid File Format\n";
        continue;
    }else
    {fstream MyReadFile(fileName);
    if(!MyReadFile)
    {
        cout << "File Not Found, Would you like to try again ? (y|n)" << endl;
        char ans;
        cin >> ans;
        ans=tolower(ans);
        switch (ans)
        {
            case 'y':
                continue;
            case 'n':
                return;
        }

    }
        string line;
        while (getline (MyReadFile, line)) {
            try {
                cout << "\n" ;
                cout << "[" <<flag<<"]";
                flag++;
                cout << line << endl;
                cout << "\n" ;
                evaluateLine(line);
            }catch (...)
            {
                return;
            }
        }
        cout << "============================\n" << endl;
        cout << "Sorted By Key\n";
        inOrder();
        cout << "\nSorted By Value\n";
        Heapsort();
    }
    system("pause");
        break;}
}
void liveInter()
{
    ClearScreen();
    cout << "Welcome to Moython Live Interpreter" << endl;
    cout << "We aren't case sensitive, Except for the Sorting Commands !" << endl;
    cout << "For heap sort type 'heapSort()'\n"
            "For inOrder Sort type 'inOrder()'\n"
            "For Quitting type 'quit()'\n"
            "PS: Break me if you can ;) " << endl;
    string x;
    while (true){
        cout << "\n" ;

        cout << "[" <<flag<<"]";
        flag++;
        cin >> x;
        if(x=="quit()")
        {
            break;
        }
        if(x=="inOrder()")
        {
            inOrder();
            continue;
        }
        if(x=="heapSort()")
        {
            Heapsort();
            continue;
        }
        cout << "\n" ;
        evaluateLine(x);
    }
}

void menu()
{
    cout << "                                   Welcome to Moython ;) "<< endl;
    cout << "                                   =====================\n" << endl;
    cout << "Choose your preferred option" << endl;
    cout << "============================\n" << endl;
    cout << "1-From file" << endl;
    cout << "2-Live Interpreter" << endl ;

    int x;
    while (true)
    {
        cin >> x;
        if(x==1||x==2)
        {
            break;
        }
        else {cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Choice\n";
            continue;}
    }
    switch (x)
    {
        case 1:
        {
fileRead();
            break;
        }
        case 2:
        {
            liveInter();
            break;
        }
        default:
            break;
    }
}
int main() {

menu();
 return 0;
}