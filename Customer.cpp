/*
 *  Implementation Invariant (explanation of design choices)
 *  genDeliveryTime()
 *  - generates int between MIN_TIME and MAX_TIME
 *  orderDelivery(int currTime)
 *  - calls construction of new Delivery object, overwriting the default invalid object with an actual object
 *  queryDelivery()
 *  - echoes Delivery's shareOrder() method
 *  payForOrder()
 *  - deducts the cost of delivery from the Customer's balance
 *  summarize()
 *  - generates a summary string
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
