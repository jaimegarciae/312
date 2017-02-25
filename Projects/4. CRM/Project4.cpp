/* 
 * EE312 Simple CRM Project
 *
 * Jaime Eugenio Garcia
 * jeg3954
 *
 */
#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
// Customer type variable used to store the inventory
Customer inventory;

void reset(void) {
	inventory.bottles = 0;
	inventory.diapers = 0;
	inventory.rattles = 0;
	num_customers = 0;
}

int checkBottles(String *type){
	int isEqual;
	String bottles = StringCreate("Bottles");
	if(StringIsEqualTo(type, &bottles)){
		isEqual = 1;
	} else{
		isEqual = 0;
	}
	StringDestroy(&bottles);
	return isEqual;
}

int checkDiapers(String *type){
	int isEqual;
	String diapers = StringCreate("Diapers");
	if(StringIsEqualTo(type, &diapers)){
		isEqual = 1;
	} else{
		isEqual = 0;
	}
	StringDestroy(&diapers);
	return isEqual;
}

int checkRattles(String *type){
	int isEqual;
	String rattles = StringCreate("Rattles");
	if(StringIsEqualTo(type, &rattles)){
		isEqual = 1;
	} else{
		isEqual = 0;
	}
	StringDestroy(&rattles);
	return isEqual;
}

void sorryMessage(int *index, String *type, int *inStock){
	printf("Sorry ");
	StringPrint(&customers[*index].name);
	printf(", we only have %d ", *inStock);
	StringPrint(type);
	printf("\n");
	return;
}

void mostBottles(){
	int max = 0;
	int index;
	for(int i = 0; i < num_customers; i++){
		if(max < customers[i].bottles){
			max = customers[i].bottles;
			index = i;
		}
	}
	if(max != 0){
		printf("no one has purchased any Bottles");
	} else{
		StringPrint(&customers[index].name);
		printf(" has purchased the most Bottles (%d)", customers[index].bottles);

	}
}

void mostDiapers(){
	int max = 0;
	int index;
	for(int i = 0; i < num_customers; i++){
		if(max < customers[i].diapers){
			max = customers[i].diapers;
			index = i;
		}
	}
	if(max != 0){
		printf("no one has purchased any Diapers");
	} else{
		StringPrint(&customers[index].name);
		printf(" has purchased the most Diapers (%d)", customers[index].diapers);

	}
}

void mostRattles(){
	int max = 0;
	int index;
	for(int i = 0; i < num_customers; i++){
		if(max < customers[i].rattles){
			max = customers[i].rattles;
			index = i;
		}
	}
	if(max != 0){
		printf("no one has purchased any Rattles");
	} else{
		StringPrint(&customers[index].name);
		printf(" has purchased the most Rattles (%d)", customers[index].rattles);

	}
}

void processSummarize() {
	printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", inventory.bottles, inventory.diapers, inventory.rattles);
	printf("we have had a total of %d different customers\n", num_customers);
	mostBottles();
	mostDiapers();
	mostRattles();
	return;
}

void makePurchase(int index, String *type, int *amount){
	if(checkBottles(type)){
		if(inventory.bottles < *amount){
			sorryMessage(&index, type, &inventory.bottles);
		} else{
			customers[index].bottles += *amount;
			inventory.bottles -= *amount;
		}
	} else if(checkDiapers(type)){
		if(inventory.bottles < *amount){
			sorryMessage(&index, type, &inventory.diapers);
		} else{
			customers[index].diapers += *amount;
			inventory.diapers -= *amount;
		}
	} else if(checkRattles(type)){
		if(inventory.bottles < *amount){
			sorryMessage(&index, type, &inventory.rattles);
		} else{
			customers[index].rattles += *amount;
			inventory.rattles -= *amount;
		}
	}
	return;
}

int customerSearch(String *name){
	for(int i = 0; i < num_customers; i++){
		if(StringIsEqualTo(name, &customers[i].name)){
			return i;
		}
	}
	customers[num_customers].name = *name;
	num_customers++;
	return (num_customers - 1);
}

void processPurchase() {
	String name, type;
	int amount;
	readString(&name);
	readString(&type);
	readNum(&amount);
	makePurchase(customerSearch(&name), &type, &amount);
	StringDestroy(&name);
	StringDestroy(&type);
}

void addToInventory(String *type, int *amount){
	if(checkBottles(type)){
		inventory.bottles += *amount;
	} else if(checkDiapers(type)){
		inventory.diapers += *amount;
	} else if(checkRattles(type)){
		inventory.rattles += *amount;
	}
	return;
}

void processInventory() {
	String type;
	int amount;
	readString(&type);
	readNum(&amount);
	addToInventory(&type, &amount);
	StringDestroy(&type);
	return;
}