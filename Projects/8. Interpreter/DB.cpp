#include "DB.h"
#include <iostream>

Variable::Variable(int value, String name) {
    this->value = value;
    this->name = name;
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

DB::~DB(){
	destroyTree(root);
}

void DB::insert(int value, String name) {
	Variable *n = find(name);
	if(n == NULL){ //Variable found, add new Variable to DB tree
		Variable *newN = new Variable(value, name);
		if(root == NULL){
			root = newN;
		} else{
			Variable *parent = NULL;
			Variable *current = root;
			//Find Variable location in DB
			while(current != NULL){
				parent = current;
				if(current->name > name){
					current = current->left;
				} else{
					current = current->right;
				}
			}
			//Insert new variable in DB
			if(parent->name > name){
				parent->left = newN;
			} else{
				parent->right = newN;
			}
			newN->parent = parent;
		}
	} else{ //Variable found, just modify value
		n->value = value;
	}
	cout<<"Totally worked bro"<<endl;
}

Variable* DB::find(String name){
	Variable* n = root;
	while(n != NULL){
		if(n->name > name){
			n = n->left;
		} else{
			n = n->right;
		}
	}
	return n;
}

void DB::destroyTree(Variable *n){
	if(n == NULL){
		return;
	}
	destroyTree(n->left);
	destroyTree(n->right);
	delete n;
}
