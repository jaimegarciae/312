#ifndef _DB_h
#define _DB_h
#include "String.h"
using namespace std;

class Variable{
  public:
    String name;
    int value;
    Variable *left;
    Variable *right;
    Variable *parent;
    Variable(int value, String name);
};

class DB{
  private:
  	Variable *root;
  	void destroyTree(Variable *n);

  public:
  	DB(void) : root(NULL) {}
  	void insert(int value, String name);
  	Variable* find(String var);
  	~DB(void);
};
#endif
