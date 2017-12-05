/*
 * Author: Jost Luebbe
 */

#include "Parse.h"
#include "BST.h"
#include "ExpTree.h"

BST sym_tab;

/*
 * When called, this function will run until it has successfully evaluated
 * the expression that followed the token from where the call was made.
 */
int evaluate_exp(){
    vector<Node*> expr;
    while((next_token_type != KEYWORD) && (next_token_type != END) && (next_token() != "//")){
        switch(next_token_type){
            case NUMBER:
                expr.push_back(new Node(true, token_number_value, "\0"));
                break;
            case SYMBOL:{
                String symbol =  next_token();
                expr.push_back(new Node(false, 0, symbol));
                if(symbol == "!" or symbol == "~")
                    expr.push_back(new Node(true, 999, "\0"));
                break;
            }
            case STRING:{
                expr.push_back(new Node(true, sym_tab.get_value(next_token()), "\0"));
                break;
            }
        }
        if(next_token_type == KEYWORD){
            break;
        }
        read_next_token();
    }
    ExpTree exprTree(expr);

    int ret = exprTree.parse();
    return ret;
}

/*
 * The text command should skip the current token (the actual text command)
 * and read the next token (the string to output) and print that string out
 * to the console
 */
void text_command(){
    read_next_token();
    String text_output = next_token();
    cout << text_output.c_str();
}

/*
 * The output command should consume the current token (the actual output command)
 * and read the next token
 * This next token has three cases:
 *      Case 1: token is a singular int
 *          In this case the output command should just print out the number it sees
 *      Case 2: token is a singular string value (presumably a variable name)
 *          In this case the output command should look for the corresponding value for
 *          that variable name
 *      Case 3: the token is a symbol other than //
 *          In this case the function evaluate_exp() is called to evaluate the expression
 *          following the command output. It should the print out the evaluated value
 *      default case:
 *          this case should never be reach and if it is, we have a big problem.
 */
void output_command(){
    read_next_token();
    switch(next_token_type){
        case NUMBER:{
            int output = token_number_value;
            cout << output;
            break;
        }
        case SYMBOL:{
            int exp_val = evaluate_exp();
            cout << exp_val;
            break;
        }
        case STRING:{
            String var_name = next_token();
            int var_value = sym_tab.get_value(var_name);
            cout << var_value;
            break;
        }
    }
}

/*
 * The var command should consume the current token (the actual var command)
 * and read the next token
 * this token will be the variable name. the first thing var should do is check if the
 * variable name already exists, and if it does, print the error message
 * it should save the variable name and consume that token and read the next
 * This next token has three cases:
 *      Case 1: token is a singular int
 *          In this case the var command should create and entry in the BST with the variable
 *          name and the value of the current token. The BST handles overwriting variables
 *          that already exists in the symbol table.
 *      Case 2: token is a singular string value (presumably a variable name)
 *          in this case the var command should use the given variable name and find that
 *          variable's value. It should then make an entry in the BST using those two values. The
 *          BST handles overwriting variables that already exists in the symbol table.
 *      Case 3: the token is a symbol other than //
 *          In this case the function evaluate_exp() is called to evaluate the expression
 *          following the var output. It should place the value into the BST using the var name
 *          and the value gotten from the expression. The BST handles overwriting variables
 *          that already exists in the symbol table.
 *      default case:
 *          this case should never be reach and if it is, we have a big problem.
 */
void var_command(){
    read_next_token();
    String name = next_token();
    if(sym_tab.is_present(name))
        cout << "variable " << name.c_str() << " incorrectly re-initialized" << endl;
    read_next_token();
    switch(next_token_type){
        case NUMBER:{
            sym_tab.insert(name, token_number_value);
            break;
        } case STRING:{
            String var_name = next_token();
            int var_value = sym_tab.get_value(var_name);
            sym_tab.insert(name, var_value);
            break;
        } case SYMBOL:{
            int exp_value = evaluate_exp();
            sym_tab.insert(name, exp_value);
            break;
        }
    }
}

void set_command(){
    read_next_token();
    String name = next_token();
    if(!(sym_tab.is_present(name)))
        cout << "variable " << name.c_str() << " not declared" << endl;
    read_next_token();
    switch(next_token_type){
        case NUMBER:{
            sym_tab.insert(name, token_number_value);
            break;
        } case STRING:{
            String var_name = next_token();
            int var_value = sym_tab.get_value(var_name);
            sym_tab.insert(name, var_value);
            break;
        } case SYMBOL:{
            int exp_value = evaluate_exp();
            sym_tab.insert(name, exp_value);
            break;
        }
    }
}

void run(){
    read_next_token();
    while(next_token_type != END){
        switch(next_token_type){
            case KEYWORD:
                if(next_token() == "text"){
                    text_command();
                } else if(next_token() == "output"){
                    output_command();
                } else if(next_token() == "var"){
                    var_command();
                } else if(next_token() == "set"){
                    set_command();
                }
                if(next_token() == "//")
                    skip_line();
                break;
            case SYMBOL:
                if(next_token() == "//")
                    skip_line();
                break;
        }
        if(next_token_type == KEYWORD){
            continue;
        }
        if(next_token_type == END){
            break;
        }
        read_next_token();
    }
}