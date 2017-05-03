#include "handler.h"
#include <iostream>
#include "Parse.h"
#include "String.h"
#include "DB.h"
#include "ET.h"
#include "PT.h"
using namespace std;
void processKey(Node*, DB&);
void processOut(Node*, DB&);
void setVariable(Node*, DB&);
void initVariable(Node*, DB&);

void run(){
    DB database;
    PT parseTree = PT();
    Node* current = parseTree.getRoot();
    while(current->key != "done"){
        processKey(current, database);
        current = current->next;
    }
}

void processKey(Node* current, DB& database){
    if(current->key == "text"){
        cout << current->output.c_str();
    } else if(current->key == "output"){
        processOut(current, database);
    } else if(current->key == "set"){
        setVariable(current, database);
    } else if(current->key == "var"){
        initVariable(current, database);
    }
    //TODO: loops and conditionals
}

void processOut(Node* current, DB& database){
    int val = current->operation->evaluate(database);
    cout << val;
}

void setVariable(Node* current, DB& database){
    int val = current->operation->evaluate(database);
    database.set(val, current->var);
}

void initVariable(Node* current, DB& database){
    int val = current->operation->evaluate(database);
    database.insert(val, current->var);
}
