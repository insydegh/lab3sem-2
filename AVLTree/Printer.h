//
// Created by fokus on 10.11.2021.
//

#pragma once



#pragma once
#include <algorithm>
#include<list>
#include <stack>
#include <iterator>
#include <iostream>
#include <string>
#include<functional>
#include<cmath>
#include <complex>
#include <sstream>
#include <vector>
#include <fstream>
#include "AVLTree.h"
using namespace std;



template<typename T>
class TreeNode {
public:
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode<T>(T value);
};

template<class T>
TreeNode<T>::TreeNode(T value) {

    this->value = value;

    this->left = NULL;
    this->right = NULL;
}





struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk *p){
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;

}

template<typename T>
void printTree(Node<T>* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->rightChild, trunk, false);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = "`---";
        prev->str = prev_str;

    }
    else {
        trunk->str = ".---";
        prev_str = "   |";
    }

    showTrunks(trunk);
    cout << root->key<<endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->leftChild, trunk, true);
}