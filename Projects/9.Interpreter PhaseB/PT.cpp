#include "PT.h"
#include <iostream>

Node::Node(){
    this->next = NULL;
    this->operation = NULL;
    this->alternate = NULL;
}

PT::~PT(void){
	destroyTree(this->root);
}

PT::PT(void){
  this->root = new Node();
  fillTree();
}

void PT::fillTree(void){
	Node* n = this->root;
	read_next_token();
	while(next_token_type != END){
        if(next_token_type == NAME){
            //Keyword encountered, command should be added to Parse Tree
            n = addKey(n);
            n->next = new Node();
            n = n->next;
        } else { 
            //Comment encountered, rest of the line is ignored
            skip_line();
        }
        read_next_token();
    }
    n->key = "done";
}

Node* PT::addKey(Node* n){
	String keyword = next_token();
	n->key = keyword;

    if(keyword == "text"){
       read_next_token();
       n->output = next_token();
    } else if(keyword == "output"){
        n->operation = new ET();
    } else if(keyword == "set" || keyword == "var"){
        read_next_token();
        String name = next_token();
        n->var = name;
        n->operation = new ET();
    } else if(keyword == "do"){
        return addLoop(n);
    } else if(keyword == "if"){
    	//return addConditional(n);
    } else{
        cout<<"This is something different: " << keyword.c_str() <<endl;
    }
    return n;
}

Node* PT::addLoop(Node* n){
    n->operation = new ET();
    Node* start = n;
    n->next = new Node();
    n = n->next;

    read_next_token();
    String keyword = next_token();
    while(keyword != "od"){
        if(next_token_type == NAME){
            //Keyword encountered, command should be added to Parse Tree inside loop
            n = addKey(n);
            n->next = new Node();
            n = n->next;
        } else { 
            //Comment encountered, rest of the line is ignored
            skip_line();
        }
        read_next_token();
        keyword = next_token();
    }
    start->loopEnd = n;
    n->key = keyword;
    return n;
}


Node* PT::getRoot(void){
    return this->root;
}

void PT::destroyTree(Node *n){
	if(n == NULL){
		return;
	}
	//TODO: maybe destroy each expression tree? Unsure
	destroyTree(n->next);
	delete n;
}
