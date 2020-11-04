//
// Created by Mohye on 04/06/2020.
//
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <math.h>
#include "myBST.h"
using namespace std;

BST::BST() {
    root=NULL;

}

Node *BST::searchBST(char *key) {
    Node *nodes = new Node();
    Node *r = NULL;
    Node *t = root;
    while (t) {
        r = t;
        int cmp = strcasecmp(t->key.data(), key);
        if (cmp == 0) {
            return t;
        } else if (cmp < 0)
        {
            t = t->right;
        } else
            t = t->left;

    }
    nodes->left = t;
    nodes->right = r;
    if(nodes->left==nodes->right)
    {
        return NULL;
    } else
    return nodes;
}

void BST::insert(string varName, double value) {
    Node *node= new Node(varName,value);
    char* key=node->key.data();
    Node *temp=NULL;
    if (root == NULL) {
        root = node;
    } else {
        temp=searchBST(key);
        if (temp->key==varName)
        {
            temp->value=value;
            return;
        }
        if (temp->left == NULL) {
            Node *p = temp->right;
            if (strcasecmp(p->key.data(), key) < 0) {
                p->right = node;
            } else {
                p->left = node;
            }
        }
    }
    free(temp);

}

void BST::inorderTrav(Node *root) {
    if(root) {
        inorderTrav(root->left);
        cout << root->key << " = " << root->value << endl;
        inorderTrav(root->right);
    }
}


Node::Node(string key, double value) {

    this->left = NULL;
    this->right = NULL;
    if(!key.empty())
    this->key = key;
    else
        this->key="";
    if(value!=NULL)
   this->value=value;
    else
        this->value=NULL;
}
Node::Node() {

    this->left = NULL;
    this->right = NULL;
    this->key="";
    this->value=NULL;
}
