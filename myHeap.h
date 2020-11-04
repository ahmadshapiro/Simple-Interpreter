//
// Created by Mohye on 05/06/2020.
//
#pragma once

#include <vector>
#include <string>
#include "myBST.h"
using namespace std;

class Heap
{
public:
    vector<pair<string,double>> arr;
    void BSTtoHeap(BST tree);
    Heap();
    pair<string ,double> getParent(int i);
    pair<string ,double> getlChild(int i);
    pair<string ,double> getrChild(int i);
    static pair<string , double > NodeToPair(Node* node);
    void SwapPairs (pair<string , double > *p1 ,pair<string , double > *p2);
    void printElemnts();
    //void heapify(int i);
    static void insert(vector<pair<string,double>> &A, int n);
    static void createHeap(vector<pair<string,double>> &A,int size);
    static pair<string,double> Delete(vector<pair<string,double>> &A,int n);
    static void heapSort(vector<pair<string,double>> &vector);
    //void heapSort();

private:
    void BSTtoVector(Node *root);
};