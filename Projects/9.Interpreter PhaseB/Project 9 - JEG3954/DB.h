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
  	void destroyDB(Variable *var);
    Variable* find(String name);
  public:
  	DB(void) : root(NULL) {}
  	void insert(int value, String name);
    void set(int value, String name);
    int get(String name);
  	~DB(void);
};
#endif