//
// Created by l4mb0 on 5/14/19.
//

#ifndef TEST_SOLVER_H
#define TEST_SOLVER_H

#include <string>
#include <map>
#include <cctype>
#include <vector>
#include <cmath>
#include "node.h"
#include "operations/operation.h"

using namespace std;

class solver {
protected:
    Node *root;
    Node *current;
    solver *subtree;

    Node *head;
    Node *tail;

public:
    solver() {
        root = current = head = tail = nullptr;
        subtree = nullptr;
    }

    string isOperator(string data) {
        if (data == "+" || data == "-" || data == "*" || data == "/" || data == "^") return data;
    }

    string isOperatorMasMenos(string data) {
        if (data == "+" || data == "-") return data;
    }

    string isNumber(string data) {
        if (data == "0" || data == "1" || data == "2" || data == "3" || data == "4" || data == "5" || data == "6" ||
            data == "7" || data == "8" || data == "9") {
            return data;
        }
    }


    void listTheString(string data) {
        auto newNode = new Node(data);
        if (!head) {
            this->head = this->tail = newNode;
        } else {
            newNode->prev = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
    }

    void colapseMasMenos() {
        if (head) {
            Node *iterador = head;
            while (iterador) {
                if (iterador->data == isOperatorMasMenos(iterador->data)) {
                    if (iterador->data == "+") {
                        if (iterador->next->data == "+") {
                            Node *sacrificio = iterador->next;
                            iterador->next = iterador->next->next;
                            iterador->next->prev = iterador;
                            delete sacrificio;
                        }
                        if (iterador->next->data == "-") {
                            iterador->data = '-';
                            Node *sacrificio = iterador->next;
                            iterador->next = iterador->next->next;
                            iterador->next->prev = iterador;
                            delete sacrificio;
                        }
                    }
                    if (iterador->data == "-") {
                        if (iterador->next->data == "+") {
                            iterador->data = '-';
                            Node *sacrificio = iterador->next;
                            iterador->next = iterador->next->next;
                            iterador->next->prev = iterador;
                            delete sacrificio;
                        }
                        if (iterador->next->data == "-") {
                            iterador->data = '+';
                            Node *sacrificio = iterador->next;
                            iterador->next = iterador->next->next;
                            iterador->next->prev = iterador;
                            delete sacrificio;
                        }
                    }
                } else iterador = iterador->next;
            }

        } else throw out_of_range("no hay nada en la lista..");
    }

    void collapseNumbers() {
        if (head) {
            string stringNumber;
            Node *iterador = head;
            auto temp = new Node("");
            auto newNode = new Node("");
            while (iterador) {
                if (iterador->data == isNumber(iterador->data)) {
                    temp = iterador->prev;
                    while (iterador->data == isNumber(iterador->data)) {
                        stringNumber += iterador->data;
                        iterador = iterador->next;
                        delete iterador->prev;
                    }
                    newNode->data = stringNumber;
                    iterador->prev = newNode;
                    newNode->next = iterador;
                    newNode->prev = temp;
                    temp->next = newNode;
                    stringNumber.clear();
                }
                iterador = iterador->next;
            }
        }
    }

    Node *treeTheList(Node *node) {
        auto iterador = node;
        while (iterador) {
            if (iterador->data == isOperator(iterador->data)) {
                node->data = iterador->data;
                node->left->data = iterador->prev->data;
                if (!iterador->next->next) { node->right->data = iterador->next->data; }
                node->right = treeTheList(node->right);
            } else iterador = iterador->next;
        }
    }

    string operatePriorityFirst(Node *root) {
        auto iterador = root;
        auto parent = root;

        ///vuelta 0 busco potencias
        while (iterador) {
            if (iterador->data == "^") {
                string result = to_string(pow(stof(iterador->left->data), stof(iterador->right->left->data)));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right=root;
                    delete iterador->left; delete iterador;
                }
                else {
                    parent->right=iterador->right;
                    delete iterador->left; delete iterador;

                }
            } else {
                parent = iterador;
                iterador = iterador->right;
            }
        }
        iterador=root;parent=root;


        ///vuelta 1 busco multiplicacion y division
        while (iterador) {
            if (iterador->data == "*") {
                string result = to_string(stof(iterador->left->data)*stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right=root;
                    delete iterador->left; delete iterador;
                }
                else {
                    parent->right=iterador->right;
                    delete iterador->left; delete iterador;

                }
            }
            else if(iterador->data=="/"){
                string result = to_string(stof(iterador->left->data)/stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right=root;
                    delete iterador->left; delete iterador;
                }
                else {
                    parent->right=iterador->right;
                    delete iterador->left; delete iterador;

                }
            }

            else {
                parent = iterador;
                iterador = iterador->right;
            }
        }
        iterador=root;parent=root;

        ///vuelta 2 busco sumas y restas
        while (iterador) {
            if (iterador->data == "+") {
                string result = to_string(stof(iterador->left->data)+stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right=root;
                    delete iterador->left; delete iterador;
                }
                else {
                    parent->right=iterador->right;
                    delete iterador->left; delete iterador;

                }
            }
            else if(iterador->data=="-"){
                string result = to_string(stof(iterador->left->data)-stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right=root;
                    delete iterador->left; delete iterador;
                }
                else {
                    parent->right=iterador->right;
                    delete iterador->left; delete iterador;

                }
            }

            else {
                parent = iterador;
                iterador = iterador->right;
            }
        }

        return root->data;
    }


};


#endif //TEST_SOLVER_H
