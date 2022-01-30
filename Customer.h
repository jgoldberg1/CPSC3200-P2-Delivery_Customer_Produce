//
// Created by jenma on 1/15/2022.
//
#include <iostream>
#include "Delivery.h"

using namespace std;
#ifndef P2_CUSTOMER_H
#define P2_CUSTOMER_H


class Customer {
private:
    //attributes
    string _name;
    string _address;
    double _balance;
    double _minPrice;
    int genDeliveryTime();
    Delivery _del;

public:
    //methods
    Customer(string name, string address, double balance, double minPrice);
    void orderDelivery();
    string queryDelivery();
    Delivery getDel();
};


#endif //P2_CUSTOMER_H
