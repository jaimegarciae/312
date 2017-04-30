#ifndef _ET_h
#define _ET_h
using namespace std;
#include "String.h"
#include "DB.h"
#include "Parse.h"

enum ET_Type{
    NUM,
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
    Member* left;
    Member* right;

    Member(void);
    void setVal(int val);
    void setOp(String op, OpType operatorType);
};

class ET{
  private:
    Member *root;
    void destroyTree(Member* m);
    int eval(Member *m);
	void fillTree(Member* m, DB& database);
    int binaryOperation(int first, int second, String op);
    int unaryOperation(int operand, String op);
  public:
    ET(DB& database);
    int evaluate();
    ~ET(void);
};
#endif
