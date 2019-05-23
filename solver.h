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

    void execute(string equation) {
        listTheString(equation);
        colapseMasMenos(head);
        collapseNumbers(head);
        treeTheList(head, root);
        cout << operatePriorityFirst(root) << endl;
    }


    void listTheString(string data) {
        for (int i = 0; i < data.length(); ++i) {
            string temp = "";
            temp.push_back(data[i]);
            auto newNode = new Node(temp);
            if (!head) {
                this->head = this->tail = newNode;
            } else {
                newNode->prev = this->tail;
                this->tail->next = newNode;
                this->tail = newNode;
                newNode->next = nullptr;
            }
        }
    }

    void colapseMasMenos(Node *head) {
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
                    if(iterador->next->data != isOperatorMasMenos(iterador->next->data)) iterador=iterador->next;
                } else iterador = iterador->next;
            }

        } else throw out_of_range("no hay nada en la lista..");
    }

    void collapseNumbers(Node *head) {
        int i=0;
        if (head) {
            string stringNumber;
            Node *iterador = head;
            auto temp = nullptr;
            stringNumber += iterador->data;
            iterador = iterador->next;
            while (iterador) {
                while (iterador->data == isNumber(iterador->data)) {
                    stringNumber += iterador->data;
                    iterador->prev->next=iterador->next;
                    iterador->next->prev=iterador->prev;
                    iterador = iterador->next;
                    delete iterador->prev;
                }
                iterador->prev->data = stringNumber;
                stringNumber.clear();
                iterador = iterador->next;
                stringNumber += iterador->data;
                iterador = iterador->next;
            }
        }
    }

    void treeTheList(Node* head, Node* root) {
        auto listIterador = head;
        auto treeIterador = root;
        while(listIterador){
            if(listIterador->next) {
                treeIterador->left=listIterador;
                listIterador=listIterador->next;
                treeIterador = listIterador;
            }
            else {
                treeIterador = listIterador;
                break;
            }
            treeTheList(listIterador->next, treeIterador->right);
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
                    iterador->right = root;
                    delete iterador->left;
                    delete iterador;
                } else {
                    parent->right = iterador->right;
                    delete iterador->left;
                    delete iterador;

                }
            } else {
                parent = iterador;
                iterador = iterador->right;
            }
        }
        iterador = root;
        parent = root;


        ///vuelta 1 busco multiplicacion y division
        while (iterador) {
            if (iterador->data == "*") {
                string result = to_string(stof(iterador->left->data) * stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right = root;
                    delete iterador->left;
                    delete iterador;
                } else {
                    parent->right = iterador->right;
                    delete iterador->left;
                    delete iterador;

                }
            } else if (iterador->data == "/") {
                string result = to_string(stof(iterador->left->data) / stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right = root;
                    delete iterador->left;
                    delete iterador;
                } else {
                    parent->right = iterador->right;
                    delete iterador->left;
                    delete iterador;

                }
            } else {
                parent = iterador;
                iterador = iterador->right;
            }
        }
        iterador = root;
        parent = root;

        ///vuelta 2 busco sumas y restas
        while (iterador) {
            if (iterador->data == "+") {
                string result = to_string(stof(iterador->left->data) + stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right = root;
                    delete iterador->left;
                    delete iterador;
                } else {
                    parent->right = iterador->right;
                    delete iterador->left;
                    delete iterador;

                }
            } else if (iterador->data == "-") {
                string result = to_string(stof(iterador->left->data) - stof(iterador->right->left->data));
                iterador->right->left->data = result;
                if (iterador == root) {
                    iterador->right = root;
                    delete iterador->left;
                    delete iterador;
                } else {
                    parent->right = iterador->right;
                    delete iterador->left;
                    delete iterador;

                }
            } else {
                parent = iterador;
                iterador = iterador->right;
            }
        }

        return root->data;
    }


};


#endif //TEST_SOLVER_H
