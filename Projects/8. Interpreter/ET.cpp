#include "ET.h"
#include <iostream>

Member::Member(){
    this->memberType = NULL;
    this->value = NULL;
    this->op = NULL;
    this->operatorType = NULL;
    this->left = NULL;
    this->right = NULL;
}

void Member::setVal(int value) {
    this->memberType = NUMBER;
    this->value = value;
}

void Member::setOp(OpType operatorType){
    this->memberType = OPERATOR;
    this->op = op;
    this->operatorType = operatorType;
}

~ET(void){
	destroyET(root);
}

ET::ET(DB& database){
	root = new Member();
	fillET(root, database);
}

void ET::fillET(Member* m, DB& database){
	read_next_token();
	if(next_token_type == NUMBER){
		m->setVal(token_number_value);
		return;
	} else if(next_token_type == NAME){
		String name = next_token();
		m->setVal(database.get(name));
	}
	String op = next_token();
	if(op == "!" || op == "~"){ //Only add left child
		m->setOp(op, UNARY);
	} else{ //Add both left and right children
		m->setOp(op, BINARY);
	}
	//Ask for help from Shashank
	m = Member(op);
	fillET(m->left);
	fillET(m->right);
}

int ET::evaluate(){
	return eval(root);
}

int ET::eval(Member *m){
	if(m->memberType == NUMBER){
		return m->value;
	} else if(m->operatorType == BINARY){
		return BinaryOperation(eval(m->left), eval(m->right), m->op);
	} else{
		return UnaryOperation(eval(m->left), m->op);
	}
}

int ET::BinaryOperation(int first, int second, String op){
	if(op == "+"){ 
		return (first + second);
	} else if(op == "-"){ 
		return (first - second);
	} else if(op == "*"){ 
		return (first*second);
	} else if(op == "/"){ 
		return (first/second);
	} else if(op == "%"){ 
		return (first%second);
	} else if(op == "&&"){ 
		if(first == 0 || second == 0){
			return 0;
		} else{
			return 1
		}
	} else if(op == "||"){
		if(first != 0 || second != 0){
			return 1;
		} else{
			return 0;
		}
	} else if(op == "<"){
		return (first < second);
	} else if(op == ">"){
		return (first > second);
	} else if(op == "=="){
		return (first == second);
	} else if(op == "!="){
		return (first != second);
	} else if(op == "<="){
		return (first <= second);
	} else if(op == ">="){
		return (first >+ second);
	}
}

int ET::UnaryOperation(int operand, String op){
	if(op == "!"){
		if(operand == 0){
			return 1;
		} else{
			return 0;
		}
	} else if(op == "~"){
		return -first;
	} 
}

void destroyET(Member *m){
	if(m == NULL){
		return;
	}
	destroyET(m->left);
	destroyET(m->right);
	delete m;
}
