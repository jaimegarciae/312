#ifndef _ET_h
#define _ET_h
using namespace std;
#include "String.h"
#include "DB.h"
#include "Parse.h"

enum ET_Type{
    NUM,
	OPERATOR,
    VAR
};

enum OpType{
    UNARY,
    BINARY
};

class Member{
  public:
    ET_Type memberType;
    String var;
    int value;
    String op;
    OpType operatorType;
    Member* left;
    Member* right;

    Member(void);
    void setVal(int val);
    void setOp(String op, OpType operatorType);
    void setVar(String name);
};

class ET{
  private:
    Member *root;
    void destroyTree(Member* m);
    int eval(Member *m, DB& database);
	void fillTree(Member* m, DB& database);
    int binaryOperation(int first, int second, String op);
    int unaryOperation(int operand, String op);
  public:
    ET(DB& database);
    int evaluate(DB& database);
    ~ET(void);
};
#endif
