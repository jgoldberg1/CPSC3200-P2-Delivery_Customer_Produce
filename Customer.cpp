//
// Created by jenma on 1/15/2022.
//
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
 * orderDelivery()
 * - orders the delivery of a Delivery object.
 * queryDelivery()
 * - returns a string with a summary of the Delivery object
 * summarize()
 * - returns a string with a summary of the Customer Object
 *
 */

/*PUT AT BOTTOM OF DOC
 *  Implementation Invariant (explanation of design choices)
 *  genDeliveryTime()
 *  - generates int between MIN_TIME and MAX_TIME
 *  orderDelivery()
 *  -
 *  queryDelivery()
 *  - echoes Delivery's shareOrder() method
 *  payForOrder()
 *  - deducts the cost of delivery from the Customer's balance
 *  summarize()
 *  - generates a summary string
 *
 *
 *
 */

#include "Customer.h"
#include "Delivery.h"

random_device rdCustomer;
mt19937 mtCustomer(rdCustomer());
uniform_int_distribution<int> distro(0, RAND_MAX);

//Preconditions: name, the customer's name; address, the customer's address; balance, the customer's balance;
// minPrice, the customer's minimum price they will pay for an order;
//Postconditions: Customer object created
Customer::Customer(string name, string address, double balance, double minPrice)
{
    _name = name;
    _address = address;
    _balance = balance;
    _minPrice = minPrice;
}

//Preconditions: None
//Postconditions: returns int between MIN_TIME and MAX_TIME
int Customer::genDeliveryTime()
{
    const int MIN_TIME = 72;
    const int MAX_TIME = 168;
    return (distro(mtCustomer) % 168 + 72);
}

//Precondition: None
//Postcondition: initializes _del to a Delivery object, calling Delivery constructor. Delivery.deliverBox() is called
//with the generated delivery time. delivery cost is deducted from Customer's balance.
void Customer::orderDelivery()
{
    if (_balance > _minPrice)
    {
        int deliveryTime = genDeliveryTime();
        _del = Delivery(_minPrice);
        _del.deliverBox(deliveryTime);
        payForOrder();
    }
}

//Precondition: None
//Postcondition: Returns a string describing the contents of the Customer's Delivery object
string Customer::queryDelivery()
{
    if (_del.getTotalCost() != 0) return _del.shareOrder();
    return "";
}

//Precondition: None
//Postcondition: cost of the Customer's Delivery object is deducted from Customer's balance
void Customer::payForOrder()
{
    if (_del.getTotalCost() != 0) _balance -= _del.getTotalCost();
}

//Precondition: None
//Postcondition: returns a string summarizing the Customer's attributes
string Customer::summarize()
{
    string report = "";
    report = "Name: " + _name + "\n";
    report = report + "Address: " + _address + "\n";
    report = report + "Balance: " + to_string(_balance) + "\n";
    report = report + "Minimum Price: " + to_string(_minPrice) + "\n";
    return report;
}
