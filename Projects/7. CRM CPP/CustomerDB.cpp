/*
 * Name: Jaime Eugenio Garcia
 * EID: jeg3954
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	//Search for customer, return if found
	for(int i = 0; i < this->length; i++){
		if(name == this->data[i].name){
			return this->data[i];
		}
	}
	//Add new customer to DB if not found
	if((this->length + 1) >= this->capacity){
		this->capacity *= 2;
		Customer *newDB = new Customer[this->capacity];
		for(int i = 0; i < this->length; i++){
			newDB[i] = this->data[i];
		}
		delete[] this->data;
		this->data = newDB;
	} 
	//Initialize new customer
	Customer newC = Customer(name);
	int index = this->length;
	this->data[index] = newC;
	this->length++;
	return this->data[index];
}

bool CustomerDB::isMember(String name) { // not done, your effort goes here
	for(int i = 0; i < this->length; i++){
		if(name == this->data[i].name){
			return true;
		}
	}
	return false;
}