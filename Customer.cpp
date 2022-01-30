//
// Created by jenma on 1/15/2022.
//

#include "Customer.h"
#include "Delivery.h"

random_device rdCustomer;
mt19937 mtCustomer(rdCustomer());
uniform_int_distribution<int> distro(0, RAND_MAX);

Customer::Customer(string name, string address, double balance, double minPrice)
{
    _name = name;
    _address = address;
    _balance = balance;
    _minPrice = minPrice;
}

int Customer::genDeliveryTime()
{
    const int MIN_TIME = 72;
    const int MAX_TIME = 168;
    return (distro(mtCustomer) % 168 + 72);
}

//Precondition:
//Postcondition:
void Customer::orderDelivery()
{
    int deliveryTime = genDeliveryTime();
    _del = Delivery(_minPrice);
    _del.deliverBox(deliveryTime);
}

//Precondition:
//Postcondition:
string Customer::queryDelivery()
{
    return _del.shareOrder();
}

Delivery getDel()
{
    return _del;
}
