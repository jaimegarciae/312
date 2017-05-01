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

void Member::setVar(String name){
	this->memberType = VAR;
	this->var = name;
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
  // If next member of the operation is a number or a variable, it is added as a leaf to the ET
  if(next_token_type == NUMBER){
    m->setVal(token_number_value);
    return;
  } else if(next_token_type == NAME){
    String name = next_token();
    m->setVar(name);
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

int ET::evaluate(DB& database){
	return eval(root, database);
}

int ET::eval(Member *m, DB& database){
	if(m->memberType == NUM){
		return m->value;
	} else if(m->memberType == VAR){
		return database.get(m->var);

	}else if(m->operatorType == BINARY){
		return binaryOperation(eval(m->left, database), eval(m->right, database), m->op);
	} else{
		return unaryOperation(eval(m->left, database), m->op);
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
		return (first < second ? 1 : 0);
	} else if(op == ">"){
		return (first > second ? 1 : 0);
	} else if(op == "=="){
		return (first == second ? 1 : 0);
	} else if(op == "!="){
		return (first != second ? 1 : 0);
	} else if(op == "<="){
		return (first <= second ? 1 : 0);
	} else if(op == ">="){
		return (first >= second ? 1 : 0);
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
