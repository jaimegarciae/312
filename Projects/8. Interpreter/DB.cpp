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
	destroyDB(root);
}

void DB::insert(int value, String name) {
	Variable *var = find(name);
	if(var == NULL){ 
		//If Variable is not found, new Variable is initialized and added to DB tree
		Variable *newVar = new Variable(value, name);
		if(root == NULL){
			//First Variable in tree is set as root
			root = newVar;
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
			//Insert new Variable in DB
			if(parent->name > name){
				parent->left = newVar;
			} else{
				parent->right = newVar;
			}
			newVar->parent = parent;
		}
	} else{
		//Variable found, output warning message and update value
		cout << "variable " << name.c_str() << " incorrectly re-initialized" << endl;
		var->value = value;
	}
}

Variable* DB::find(String name){
	Variable* var = root;
	while(var != NULL && name != var->name){
		if(var->name > name){
			var = var->left;
		} else{
			var = var->right;
		}
	}
	return var;
}

void DB::set(int value, String name){
	Variable* var = find(name);
    if(var == NULL){
        cout << "variable " << name.c_str() << " not declared" << endl;
        insert(value, name);
    }else{
		var->value = value;
    }
}

int DB::get(String name){
	Variable* var = find(name);
	if(var){
		return var->value;
	}
}

void DB::destroyDB(Variable *var){
	if(var == NULL){
		return;
	}
	destroyDB(var->left);
	destroyDB(var->right);
	delete var;
}
