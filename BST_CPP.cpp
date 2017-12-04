// BST_CPP.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "BST.h"

#include <string>
using std::string;

void doit(BST fred) {
	fred.remove("good");
	printf("fred: ");
	fred.print("%s");
}

int main(void) {
	BST my_tree;

	my_tree.insert("x", 4);
	my_tree.insert("y", 10);
/*	my_tree.insert("good");
	my_tree.insert("chai");
	my_tree.insert("book");
	my_tree.insert("dove");*/
	printf("my_tree: ");
	my_tree.print("%s");
	my_tree.remove("x");
	printf("my_tree: ");
	my_tree.print("%s");
	//doit(my_tree);
	//printf("my_tree: ");
	my_tree.print("%s");
    my_tree.printRecursive();
    return 0;

}