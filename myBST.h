//
// Created by Mohye on 04/06/2020.
//
#pragma once

#include <vector>

using namespace std;

class Node {
public:
    Node(string key, double value);
    Node();
    string key;
    struct Node *left;
    struct Node *right;
    double value;

};

class BST {
public:
    Node * searchBST(char *key);
    void insert(string key, double value);
    void inorderTrav(Node *x);
    Node *root;
public:
    BST();
} ;
//Node *newNode(string key, double value);

//BST::BST *newBST() ;
//Node * searchBST(BST *tree, char *key);
//Node* copyNode(Node* node);
//void insert(BST *tree, Node* newNode);
//void inorderTrav(Node *root);