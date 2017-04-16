using namespace std;
#include "String.h"

enum ET_Type{
	NUMBER,
	OPERATOR,
	VARIABLE
};

class ET{
  private:
  	class Node{
  		int value;
  		ET_Type type;
  		Node *left;
  		Node* right;
  		Node(int value)
  	}
};