#include "handler.h"
#include <iostream>
#include "Parse.h"
#include "String.h"
#include "DB.h"
#include "ET.h"
#include "PT.h"
using namespace std;
Node* processKey(Node*, DB&);
void processOut(Node*, DB&);
void setVariable(Node*, DB&);
void initVariable(Node*, DB&);
Node* doLoop(Node*, DB&);
Node* doCond(Node* current, DB& database);

void run(){
    DB database;
    PT parseTree = PT();
    Node* current = parseTree.getRoot();
    while(current->key != "done"){
        current = processKey(current, database);
        current = current->next;
    }
}

Node* processKey(Node* current, DB& database){
    if(current->key == "text"){
        cout << current->output.c_str();
    } else if(current->key == "output"){
        processOut(current, database);
    } else if(current->key == "set"){
        setVariable(current, database);
    } else if(current->key == "var"){
        initVariable(current, database);
    } else if(current->key == "do"){
        current = doLoop(current, database);
    } else if(current->key == "if"){
        current = doCond(current, database);
    }
    return current;
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

Node* doLoop(Node* current, DB& database){
    Node* loopStart = current;
    if(current->operation->evaluate(database)){
        current = current->next;
        while(current->key != "od"){
            current = processKey(current, database);
            current = current->next;
        } 
        current = doLoop(loopStart,database);
    }
    return loopStart->loopEnd;
}

Node* doCond(Node* current, DB& database){
    if(!current->operation->evaluate(database)){
        current = current->alternate;
    } else{
        current = current->next;
    }
    
    while(current->key != "fi"){
        current = processKey(current, database);
        current = current->next;
    }
    return current;
}