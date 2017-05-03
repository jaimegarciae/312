#ifndef _PT_h
#define _PT_h
using namespace std;
#include "String.h"
#include "DB.h"
#include "ET.h"
#include "Parse.h"

class Node{
  public:
    String key;
    Node* next;
    Node* loop;
    Node* other;
    String var;
    ET* operation;
    String output;
    //TODO: pointer to function

    Node(void);
};

class PT{
  private:
    Node *root;
    void destroyTree(Node* n);
    void fillTree(void);
    Node* addKey(Node* current);
  public:
    PT(void);
    ~PT(void);
    //TODO: Implement a way to control the flow of instructions
    Node* getRoot(void);
};
#endif
