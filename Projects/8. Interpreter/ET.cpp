#include "ET.h"
#include <iostream>

Member::Member(){
    this->left = NULL;
    this->right = NULL;
}

void Member::setVal(int value) {
    this->memberType = NUM;
    this->value = value;
}

void Member::setOp(String op, OpType operatorType){
    this->memberType = OPERATOR;
    this->op = op;
    this->operatorType = operatorType;
}

ET::~ET(void){
	destroyTree(this->root);
}

ET::ET(DB& database){
  this->root = new Member();
  fillTree(this->root, database);
}

void ET::fillTree(Member* m, DB& database){
  if (m == NULL) return;
  read_next_token();
  if(next_token_type == NUMBER){
    m->setVal(token_number_value);
    return;
  } else if(next_token_type == NAME){
    String name = next_token();
    m->setVal(database.get(name));
    return;
  }
  String op = next_token();
  if(op == "!" || op == "~"){
    m->setOp(op, UNARY);
  } else{ 
    m->setOp(op, BINARY);
    m->right = new Member();
  }
  m->left = new Member();

  fillTree(m->left, database);
  fillTree(m->right, database);
}

int ET::evaluate(){
	return eval(root);
}

int ET::eval(Member *m){
	if(m->memberType == NUM){
		return m->value;
	} else if(m->operatorType == BINARY){
		return binaryOperation(eval(m->left), eval(m->right), m->op);
	} else{
		return unaryOperation(eval(m->left), m->op);
	}
}

int ET::binaryOperation(int first, int second, String op){
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
			return 1;
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

int ET::unaryOperation(int operand, String op){
	if(op == "!"){
		if(operand == 0){
			return 1;
		} else{
			return 0;
		}
	} else if(op == "~"){
		return -operand;
	} 
}

void ET::destroyTree(Member *m){
	if(m == NULL){
		return;
	}
	destroyTree(m->left);
	destroyTree(m->right);
	delete m;
}
