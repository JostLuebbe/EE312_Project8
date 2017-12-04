//
// Created by jostl on 11/14/2017.
//

#include "Parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "String.h"
#include "BST.h"
#include "ExpTree.h"

using namespace std;

BST sym_tab;

int evaluate_exp(){
    vector<Node*> expr;
    int before_isnumber = false;
    read_next_token();
    while((next_token_type != KEYWORD) && (next_token_type != END) && (next_token() != "//")){
        switch(next_token_type){
            case NUMBER:
                expr.push_back(new Node(true, token_number_value, "\0"));
                peek_next_token();
                if((next_token_type != SYMBOL) and (next_token_type != STRING) and (next_token_type != NUMBER) and before_isnumber){
                    expr.push_back(new Node(true, 999, "\0"));
                }
                before_isnumber = false;
                break;
            case SYMBOL:
                expr.push_back(new Node(false, 0, next_token()));
                before_isnumber = true;
                break;
            case STRING:
                expr.push_back(new Node(true, sym_tab.get_value(next_token()), "\0"));
                before_isnumber = true;
                break;
            default:
                cout << "SHOULDNT BE HERE";
        }
        peek_next_token();
        if(next_token_type == KEYWORD)
            break;
        read_next_token();
    }
    ExpTree exprTree(expr);
    int ret = exprTree.parse();
    return ret;
}

void run(){
    read_next_token();
    while(next_token_type != END){
        switch(next_token_type){
            case KEYWORD:
                if(next_token() == "text"){
                    read_next_token();
                    // if its the text command we should just immediately output the next token
                    cout << next_token().c_str();
                } else if(next_token() == "output"){
                    cout << evaluate_exp();
                } else if(next_token() == "var"){
                    read_next_token();
                    String name = next_token();
                    if(sym_tab.is_present(name))
                        cout << "variable " << name.c_str() << " incorrectly re-initialized" << endl;
                    read_next_token();
                    switch(next_token_type){
                        case NUMBER:
                            sym_tab.insert(name, token_number_value);
                            break;
                        case STRING:
                            sym_tab.insert(name, token_number_value);

                        default:
                            cout << "NOPE2" << endl;
                    }
                } else if(next_token() == "set"){}
                if(next_token() == "//")
                    skip_line();
                break;
            case STRING:
                printf("HERE\n");
                cout << next_token().c_str();
                break;
            case NUMBER:
                break;
            case SYMBOL:
                //printf("%s\n", peek_next_token());
                if(next_token() == "//")
                    //printf("HERE");
                    skip_line();
                break;
            default:
                cout << "NOPE 1";
        }
        read_next_token();
    }
}

int main(void) {
/*    string a(" + + 2 3 - 4 5"); // expression to be parsed
    const int size = 7;
    Node* nodes [size]; // create set of Nodes, one for each token
    nodes[0] = new Node(false, 0, '+');
    nodes[1] = new Node(false, 0, '+');
    nodes[2] = new Node(true, 2, '\0');
    nodes[3] = new Node(true, 3, '\0');
    nodes[4] = new Node(false, 0, '-');
    nodes[5] = new Node(true, 4, '\0');
    nodes[6] = new Node(true, 5, '\0');
    vector<Node*> expr;
    for (int i = 0; i < size; i++) { // add Nodes to expression expr
        expr.push_back(nodes[i]);
    }
    cout << endl;

    ExpTree myTree(expr); // make a tree using the expression expr

    cout << endl;
    myTree.printTree(); // print out the expression tree (sideways)

    BST my_tree;

    my_tree.insert("x", 4);
    my_tree.insert("y", 10);
    my_tree.insert("a", 9);
    my_tree.insert("b", 8);
    my_tree.insert("u", 6);
    my_tree.insert("c", 3);
    printf("my_tree: ");
    my_tree.print();
    if(my_tree.is_present("a")){
        printf("%d\n", my_tree.get_value("a"));
    }
    if(my_tree.is_present("d")){
        printf("%d\n", my_tree.get_value("a"));
    }
    printf("%d\n", my_tree.get_value("b"));
    printf("%d\n", my_tree.get_value("c"));
    printf("%d\n", my_tree.get_value("u"));
    printf("%d\n", my_tree.get_value("x"));
    printf("%d\n", my_tree.get_value("y"));
    printf("my_tree: ");
    my_tree.print();
    delete &my_tree;*/

/*    cout << " ------------ Test 1 ------------ " << endl;
    set_input("test1.blip");
    run();

    cout << " ------------ Test 2 ------------ " << endl;
    set_input("test2.blip");
    run();*/

/*    cout << " ------------ Test 3 ------------ " << endl;
    set_input("test3.blip");
    run();*/

    cout << " ------------ Test 4 ------------ " << endl;
    set_input("test4.blip");
    run();

    return 0;
}