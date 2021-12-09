#pragma once

#include <iostream>
#include <algorithm>
#include <stack>
#include "ListSequence.h"

template <typename T>
struct Node
{
	T key;
	int height;
	Node<T>* leftChild;
	Node<T>* rightChild;

    Node()
    {
        leftChild = rightChild = nullptr;
        height = 0;
    }

	Node(T key) : key(key)
    {
        leftChild = rightChild = 0;
        height = 0;
    }

    bool isLeafNode() const
    {
        return !(leftChild || rightChild);
    }
};


template <typename T>
class AVL
{

public:
    AVL()
    {
        this->root = nullptr;
    }

    AVL(const AVL<T>& that)
    {
        if (that.root == nullptr)
        {
            this->root = nullptr;
            return;
        }

        //passed the node of this tree and the node of that tree by reference and recursively deep copies.
        copy(this->root, that.root);
    }


    int getHeight() const
    {
        if (root)
            return root->height;
        else return 0;
    }

    void insert(T key)
    {

        root = insert(this->root, key);
    }


    Node<T>* search(T key) const
    {
        return search(this->root, key);
    }


    void deleteAll()
    {
        deleteAll(this->root);
        this->root = nullptr;
    }

    void deleteKey(T const key)
    {
        this->root = deleteKey(this->root, key);
    }

    int length() const
    {
        return length(this->root);
    }


    bool IsBalanced(){
        return is_balanced(root);
    }

    Node<T>* getRoot() const {
        return root;
    }

    Sequence<Node<T>*>* Threading(string method = "LNR") {
        Sequence<Node<T>*>* list =new ListSequence<Node<T>*>();
        if (!root) {
            return list;
        }
        _ToThread(root, list, method);
        return list;
    }

    string toString(string method) {
        string str;
        if (!root) {
            std::cout << "Tree is empty" << std::endl;
            return str;
        }
        Sequence<Node<T>*>* list = this->Threading(method);
        for (int i = 0; i < list->GetSize(); i++) {
            str += to_string(list->Get(i)->key);
            if (i < list->GetSize() - 1) {
                str += " ";
            }
        }
        return str;
    }

    ~AVL()
    {
        deleteAll();
    }


private:
    Node<T>* root;

    int getHeight(Node<T>* root) const
    {
        if (root == nullptr)
            return -1;

        if (root->isLeafNode())
            return 0;

        return root->height;

    }

    void updateHeight(Node<T>* root) const
    {
        if (!root->isLeafNode())
            root->height = 1 + std::max(getHeight(root->leftChild), getHeight(root->rightChild));
        else root->height = 0;
    }

    int length(Node<T>* node) const
    {
        if (node == nullptr)
            return 0;

        else return (1 + length(node->leftChild) + length(node->rightChild));
    }

    void copy(Node<T>*& n1, Node<T>const* const& n2)
    {
        if (n2 == nullptr)
        {
            n1 = nullptr;
            return;
        }

        n1 = new Node<T>;
        n1->key=n2->key;
        n1->height = n2->height;

        //recursively deep copying the left subtree and the right subtree.
        copy(n1->leftChild, n2->leftChild);
        copy(n1->rightChild, n2->rightChild);

    }

    Node<T>* doubleRightLeftRotation(Node<T>* root)
    {
        Node<T>* z = root;

        Node<T>* y = z->rightChild;


        z->rightChild = this->singleRightRotation(y);

        updateHeight(z);

        z = this->singleLeftRotation(z);


        root = z;
        return root;
    }

    Node<T>* doubleLeftRightRotation(Node<T>* root)
    {
        Node<T>* z = root;
        Node<T>* y = z->leftChild;


        z->leftChild = this->singleLeftRotation(y);

        updateHeight(z);

        //z is now x
        z = this->singleRightRotation(z);

        root = z;
        return root;
    }

    Node<T>* singleRightRotation(Node<T>* root)
    {

        Node<T>* z = root;
        Node<T>* y = z->leftChild;


        Node<T>* T3 = y->rightChild;

        y->rightChild = z;
        z->leftChild = T3;

        updateHeight(z);
        updateHeight(y);

        root = y;
        return root;
    }

    Node<T>* singleLeftRotation(Node<T>* root)
    {

        Node<T>* z = root;
        Node<T>* y = z->rightChild;


        Node<T>* T2 = y->leftChild;



        y->leftChild = z;
        z->rightChild = T2;


        updateHeight(z);
        updateHeight(y);

        root = y;
        return root;
    }

    int getBalanceFactor(Node<T>* root) const
    {
        if (!root || root->isLeafNode())
            return 0;

        return getHeight(root->leftChild) - getHeight(root->rightChild);
    }

    Node<T>* insert(Node<T>* root, T key)
    {
        if (root == nullptr)
        {
            root = new Node<T>(key);
            root->height = 0;
            return root;

        }

        else if (key > root->key)
        {
            root->rightChild = insert(root->rightChild, key);

        }

        else if (key < root->key)
        {
            root->leftChild = insert(root->leftChild, key);

        }


        updateHeight(root);

        //left left case
        if (getBalanceFactor(root) > 1 && key < root->leftChild->key)
        {

            root = this->singleRightRotation(root);
        }

            //right right case
        else if (getBalanceFactor(root) < -1 && key > root->rightChild->key)
        {
            root = this->singleLeftRotation(root);
        }

            //left right case
        else if (getBalanceFactor(root) > 1 && key > root->leftChild->key)
        {
            root = this->doubleLeftRightRotation(root);
        }

            //right left case
        else if (getBalanceFactor(root) < -1 && key < root->rightChild->key)
        {
            root = this->doubleRightLeftRotation(root);
        }

        return root;

    }


    Node<T>* search(Node<T>* n,  T key) const
    {
        if (n == nullptr)
            return nullptr;

        if (n->key == key)
            return n;

        else if (key < n->key)
            return search(n->leftChild, key);

        else return search(n->rightChild, key);

    }

    void deleteAll(Node<T>* n)
    {
        if (n == nullptr)
            return;

        deleteAll(n->leftChild);
        deleteAll(n->rightChild);
        delete n;
    }

    Node<T>* deleteKey(Node<T>* root, T key)
    {
        //the key to delete does not exist in the tree.
        if (root == nullptr)
            return nullptr;

        else if (key > root->key)
        {	//move to the right subtree
            root->rightChild = deleteKey(root->rightChild, key);

        }

        else if (key < root->key)
        {	//move to the left subtree
            root->leftChild = deleteKey(root->leftChild, key);
        }

        else //root node (the passed parameter) has the key that we need to delete
        {

            //case 1: the node to delete is the leaf node.
            if (root->isLeafNode() == true)
            {
                delete root;
                return nullptr;
            }//end of case 1

                //case 2: one of the subtrees of current is nullptr;
            else if (root->leftChild == nullptr || root->rightChild == nullptr)
            {
                if (root->leftChild == nullptr)
                {
                    Node<T>* nodeToDelete = root;
                    root = root->rightChild;
                    delete nodeToDelete;

                }

                else //right child is nullptr, but left child is not
                {
                    Node<T>* nodeToDelete = root;
                    root = root->leftChild;
                    delete nodeToDelete;

                }

            }//end of case 2

            else  //case 3: none of the subtrees of node to delete is nullptr.
            {
                Node<T>* newNodeToDelete = root->rightChild;

                while (newNodeToDelete->leftChild != nullptr)
                {
                    newNodeToDelete = newNodeToDelete->leftChild;
                }

                root->key = newNodeToDelete->key;

                //in this new recursive call, case 0 and 3 will never exist. Only case 1 or case 2 will exist.
                root->rightChild = deleteKey(root->rightChild, root->key);
            }//end of case 3.
        }

        //update root height
        updateHeight(root);

        //balance the root.

        //left left case
        if (getBalanceFactor(root) > 1 && getBalanceFactor(root->leftChild) > 1)
        {

            root = this->singleRightRotation(root);
        }

            //right right case
        else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->rightChild) < -1)
        {
            root = this->singleLeftRotation(root);
        }

            //left right case
        else if (getBalanceFactor(root) > 1 && getBalanceFactor(root->leftChild) < -1)
        {
            root = this->doubleLeftRightRotation(root);
        }

            //right left case
        else if (getBalanceFactor(root) < -1 && getBalanceFactor(root->rightChild) > 1)
        {
            root = this->doubleRightLeftRotation(root);
        }

        return root;
    }

    bool is_balanced(Node<T>* root) {
        if (root == nullptr) {
            return true;
        }

        return (abs(getBalanceFactor(root)) <= 1) and is_balanced(root->rightChild) and is_balanced(root->leftChild);
    }

    void _ToThread(Node<T>* node, Sequence<Node<T>*>* list, string method) {
        using pair = pair<Node<T>*, bool>;
        stack<pair> stack;
        stack.push(pair{node, false});
        string round_name = method;
        reverse(round_name.begin(), round_name.end());
        while (!stack.empty()) {
            pair current_node = stack.top();
            stack.pop();
            if (current_node.second)
                list->Append(current_node.first);
            else {
                if (current_node.first == nullptr)
                    continue;
                for (auto ch : round_name)
                    switch (ch) {
                        case 'N':
                            stack.push(pair{current_node.first, true});
                            break;
                        case 'L':
                            stack.push(pair{current_node.first->leftChild, false});
                            break;
                        case 'R':
                            stack.push(pair{current_node.first->rightChild, false});
                            break;
                    }
            }
        }
    }








};