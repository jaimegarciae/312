#ifndef _ET_h
#define _ET_h
using namespace std;
#include "String.h"
#include "DB.h"
#include "Parse.h"

enum ET_Type{
    NUMBER,
	  OPERATOR
};

enum OpType{
    UNARY,
    BINARY
};

class Member{
  public:
    ET_Type memberType;
    int value;
    String op;
    OpType operatorType;
    Node*left;
    Node*right;

    Member(void);
    void setVal(int val);
    void setOp(OpType operatorType);
};

class ET{
  private:
    Member *root;
    void destroyET(Member *m);
    int eval(Member *m);
  public:
    ET(void) : root(NULL) {}
    void fillET();
    int evaluate();
    ~ET(void);
};
#endif
