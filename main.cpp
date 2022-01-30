
//
// Created by jenma on 1/16/2022.
//

#include <iostream>
#include <queue>
#include "Delivery.h"
#include "Produce.h"
#include "Customer.h"

int main() {
    queue<Delivery> delQ;
    Customer c = Customer("Jenna", "412 Gall Street", 1000, 200);
    delQ.push(c.Delivery)
    //cout << "querying" << endl;
    //cout << c.queryDelivery() << endl;

    //Produce* tempArr = del.forecastDelivery(200);
    //Produce p1 = Produce("apple", "fungus", 6.9, 420, "refrigerate", 666);
    //Produce p2 = Produce("orange", "vegetable", 1.2, 3, "dark", 456);
    //p1 = p2;
    //cout << "newGuy name: " << p1.getName() << " newGuy cost: " << p1.getCost() << endl;
    //del.forecastDelivery(200)->getName();
    //del.fillBox(tempArr);
    //cout << del.shareOrder();
    //cout << "newGuy name: " << tempArr->getName() << " newGuy cost: " << tempArr->getCost() << endl;

    return 0;
}