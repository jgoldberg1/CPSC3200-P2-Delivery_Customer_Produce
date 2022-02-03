
/*
 * Class Invariant (description of class)
 *    The purpose of this class is to simulate a customer of the service that creates Deliveries. The customer has a
 * balance representing how much money they have to spend on deliveries, and a minimum total price that they want their
 * delivery to cost. If the customer has more money in their balance than their minimum price, they can place a
 * delivery. Just like in real life, groceries can add up and the customer can order more than what they have in their
 * balance. When this happens, the customer will have a negative balance and not be able to order more. A customer also
 * has identifying information like a name and an address.
 *    When a customer orders a delivery, they specify a delivery time. A Delivery object is created with Produce items.
 * No expired items are delivered. A customer can also query their delivery and receive a summary of the items to be
 * delivered. Finally, a summary of the customer can be queried which includes information about the customer's
 * attributes.
 *
 *
 * Interface Invariant (explanation of public methods)
 * orderDelivery(int currTime)
 * - orders the delivery of a Delivery object.
 * - ONLY works if _balance > _minPrice, i.e. if the Customer has enough money.
 * queryDelivery()
 * - returns a string with a summary of the Delivery object
 * summarize()
 * - returns a string with a summary of the Customer Object
 *
 */
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
    void payForOrder();
public:
    Customer(string name, string address, double balance, double minPrice);
    void orderDelivery();
    string queryDelivery();
    string summarize();
};


#endif //P2_CUSTOMER_H
