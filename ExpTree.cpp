#include "ExpTree.h"

ExpTree::ExpTree(vector<Node*>& expr) { // construct from expression vector
    overallRoot = add(overallRoot, expr);
}

// private method
Node* ExpTree::add(Node* root, vector<Node*>& expr) { // passing expr as a reference
    Node* first = expr[0]; // store the first element
    expr.erase(expr.begin()); // remove the first element
    root = first; // root points to the first token Node
    if (!(first->isOperand)) { // if first is an operator, add 2 operands
        root->left = add(root->left, expr);
        root->right = add(root->right, expr);
    }
    return root; // return the new sub-tree
}

void ExpTree::printTree() {
    printTree(overallRoot, 0); // call helper method
}

void ExpTree::printSpaces(int level) { // print 4 spaces per level, for indentation
    for (int i = 0; i < level*4; i++) {
        cout << ' ';
    }
}

// private recursive helper method
void ExpTree::printTree(Node* root, int level) {
    if (root == nullptr) return;
    printTree(root->right, level+1); // print the right sub-tree
    printSpaces(level); // print the indentation for the root of sub-tree
    root->print(); // print the root
    printTree(root->left, level+1); // print the left sub-tree
}

int ExpTree::parse() {
    return parse(overallRoot);
}

int operate(String optr, int arg1, int arg2){
    if(optr == "+"){
        return arg1 + arg2;
    } else if(optr == "-"){
        return arg1 - arg2;
    } else if(optr == "*"){
        return arg1 * arg2;
    } else if(optr == "/"){
        return arg1 / arg2;
    } else if(optr == "%"){
        return arg1 % arg2;
    } else if(optr == "&&"){
        return arg1 && arg2;
    } else if(optr == "||"){
        return arg1 || arg2;
    } else if(optr == "<"){
        return arg1 < arg2;
    } else if(optr == ">"){
        return arg1 > arg2;
    } else if(optr == "=="){
        return arg1 == arg2;
    } else if(optr == "!="){
        return arg1 != arg2;
    } else if(optr == "<="){
        return arg1 <= arg2;
    } else if(optr == ">="){
        return arg1 >= arg2;
    } else if(optr == "!"){
        return (!arg2);
    } else if(optr == "~"){
        return arg2 * -1;
    }
}

int ExpTree::parse(Node* root) {
    if (root->isOperand) return root->operand;
    int arg1 = parse(root->left);
    int arg2 = parse(root->right);
    return operate(root->optr, arg1, arg2);
}
