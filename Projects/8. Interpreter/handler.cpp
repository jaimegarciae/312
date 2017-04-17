#include "handler.h"
#include <iostream>
#include "Parse.h"
#include "String.h"
#include "DB.h"
#include "ET.h"
using namespace std;
void processKey(DB&);
void processText();
void processOut(DB&);
void setVariable(DB&);
void initVariable(DB&);
int processOperation();

void run(){
    DB database;
    read_next_token();
    while(next_token_type != END){
        //Where keywords are read and handled
        if(next_token_type == NAME){
            processKey(database);
        } else if(next_token_type == SYMBOL){ //Encountered comment or error
            //TODO: handle comments vs errors
            //Currently assumes comment if not keyword
            skip_line();
        }
        read_next_token();
    }
}

void processKey(DB& database){
    String keyword = next_token();
    if(keyword == "text"){
        processText();
    } else if(keyword == "output"){
        processOut(database);
    } else if(keyword == "set"){
        setVariable(database);
    } else if(keyword == "var"){
        initVariable(database);
    }
}

void processText(){
    read_next_token();
    String toPrint = next_token();
    cout << toPrint.c_str();
}

void processOut(DB& database){
    ET operation = ET(database);
    int val = operation.evaluate();
    cout << val;
}

void setVariable(DB& database){
    read_next_token();
    String name = next_token();
    ET operation = ET(database);
    int val = operation.evaluate();
    database.set(val, name);
}

void initVariable(DB& database){
    read_next_token();
    String name = next_token();
    ET operation = ET(database);
    int val = operation.evaluate();
    database.insert(val, name);
    read_next_token();
}