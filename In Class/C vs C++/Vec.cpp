#include <iostream>
#include <stdint.h>

//Tells us whatever is in this std space, make it available for use here
using namespace std;

class Vec{
	//These values are private, they can only be accessed from within the class
	int32_t *data;
	uint32_t len;
	uint32_t cap;
  public: 
	uint32_t size(){
		//"this" is the default (implicit) argument
		return this->len;
	}
};

int main(void){
	Vec v;
	cout << v.size() << endl;
	return 0;
}