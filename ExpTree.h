#include <vector>
#include <iostream>
#include "String.h"

using namespace std;

class Node {
public:
    bool isOperand;
    int operand;
    String optr;
    Node* left;
    Node* right;
    Node(bool isOperand, int operand, String optr) {
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->optr = optr;
    }
    void print() {
        if (isOperand) {
            cout << operand << endl;
        } else {
            cout << optr.c_str() << endl;
        }
    }
};
class ExpTree {
private:
    const int spaces_per_level = 4;
    Node* overallRoot;
    Node* add(Node* root, vector<Node*>&);
    void printTree(Node*, int);
    void printSpaces(int);
    int parse(Node*);
public:
    int parse();
    ExpTree(vector<Node*>& expr); // constructor
    void printTree();
};
