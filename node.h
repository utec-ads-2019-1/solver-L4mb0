//
// Created by l4mb0 on 5/16/19.
//

#ifndef TEST_NODE_H
#define TEST_NODE_H

#include <iostream>
using namespace std;

class Node {
protected:
    string data;
    Node *left;
    Node *right;
    Node *next;
    Node*prev;


public:
    friend class solver;

    Node(basic_string<char> data){
        left = right = nullptr;
        this->data = data;
    };

    void genocidio(){
        if (left) left->genocidio();
        if (right) right->genocidio();
        delete this;
    };





};



#endif //TEST_NODE_H
