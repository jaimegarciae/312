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
Customer stock;

void reset(void) {
    stock.bottles = 0;
    stock.diapers = 0;
    stock.rattles = 0;
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

void sorryMessage(String *name, String *type, int *inStock){
    printf("Sorry ");
    StringPrint(name);
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
    if(max == 0){
        printf("no one has purchased any Bottles \n");
    } else{
        StringPrint(&customers[index].name);
        printf(" has purchased the most Bottles (%d) \n", customers[index].bottles);

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
    if(max == 0){
        printf("no one has purchased any Diapers \n");
    } else{
        StringPrint(&customers[index].name);
        printf(" has purchased the most Diapers (%d) \n", customers[index].diapers);

    }
    return;
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
    if(max == 0){
        printf("no one has purchased any Rattles \n");
    } else{
        StringPrint(&customers[index].name);
        printf(" has purchased the most Rattles (%d) \n", customers[index].rattles);

    }
}

void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", stock.bottles, stock.diapers, stock.rattles);
    printf("we have had a total of %d different customers\n", num_customers);
    mostBottles();
    mostDiapers();
    mostRattles();
    return;
}

int customerSearch(String *name){
    for(int i = 0; i < num_customers; i++){
        if(StringIsEqualTo(name, &customers[i].name)){
            return i;
        }
    }
    customers[num_customers].name = StringDup(name);
    customers[num_customers].bottles = 0;
    customers[num_customers].diapers = 0;
    customers[num_customers].rattles = 0;
    num_customers++;
    return (num_customers - 1);
}

void makePurchase(String *type, String *name, int amount){
    if(checkBottles(type)){
        if(stock.bottles < amount){
            sorryMessage(name, type, &stock.bottles);
        } else{
            customers[customerSearch(name)].bottles += amount;
            stock.bottles -= amount;
        }
    } else if(checkDiapers(type)){
        if(stock.diapers < amount){
            sorryMessage(name, type, &stock.diapers);
        } else{
            customers[customerSearch(name)].diapers += amount;
            stock.diapers -= amount;
        }
    } else if(checkRattles(type)){
        if(stock.rattles < amount){
            sorryMessage(name, type, &stock.rattles);
        } else{
            customers[customerSearch(name)].rattles += amount;
            stock.rattles -= amount;
        }
    }
    return;
}

void processPurchase() {
    String name, type;
    int amount;
    readString(&name);
    readString(&type);
    readNum(&amount);
    if(amount > 0){
        makePurchase(&type, &name, amount);
        StringDestroy(&name);
        StringDestroy(&type);
    }
    return;
}

void addToInventory(String *type, int amount){
    if(checkBottles(type)){
        stock.bottles += amount;
    } else if(checkDiapers(type)){
        stock.diapers += amount;
    } else if(checkRattles(type)){
        stock.rattles += amount;
    }
    return;
}

void processInventory() {
    String type;
    int amount;
    readString(&type);
    readNum(&amount);
    addToInventory(&type, amount);
    StringDestroy(&type);
    return;
}