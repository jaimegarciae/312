#include "handler.h"
#include <iostream>
#include "Parse.h"
#include "String.h"
#include "DB.h"
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
        } else{
            cout<< "Error, expecting keyword" << endl;
            skip_line();
        }
        read_next_token();
    }
}

void processKey(DB& database){
    string keyword = next_token();
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
    read_next_token();
    if(next_token_type == NUMBER){
        int val = token_number_value;
        cout << val;
    } else{
        //Handle expression with expression tree
        int val = processOperation();
        cout << val;
    }
}

void setVariable(DB& database){

}

void initVariable(DB& database){
    read_next_token();
    String name = next_token();
    read_next_token();
    if(next_token_type == NUMBER){
        database.insert(token_number_value, name);
    } else{
        //Handle expression with expression tree
        int val = processOperation();
        cout << val;
    }
}

int processOperation(){
    return 0;
}