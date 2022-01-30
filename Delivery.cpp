//
// Created by jenma on 1/15/2022.
//
#include <iostream>
#include <cstdlib>
#include <random>
#include "Delivery.h"
#include "Produce.h"

random_device rdDelivery;
mt19937 mtDelivery(rdDelivery());
uniform_int_distribution<int> distroDelivery(0, RAND_MAX);
uniform_real_distribution<double> distroDoubleDelivery(0, RAND_MAX);


Delivery::Delivery()
{
    _numItems = -1;
    _maxSize = -1;
}


//Constructor
Delivery::Delivery(int minPrice)
{
    Produce* newProduce = forecastDelivery(minPrice);
    fillBox(newProduce);
    //cout << "exiting constructor" << endl;
}

void Delivery::copy(const Delivery& src)
{
    _numItems = src._numItems;
    _maxSize = src._maxSize;
    deliveryItems = new Produce[_numItems];
    for (int i = 0; i < _numItems; i++)
    {
        deliveryItems[i] = src.deliveryItems[i];
    }

}

//Copy Constructor
Delivery::Delivery(const Delivery& src)
{
    copy(src);
}

Delivery& Delivery::operator=(Delivery& src)
        {
            if (this == &src) return *this;
            copy(src);
            return *this;
        }


//is this correct?? do i delete???
//also maybe make another zeroOut func
Delivery::Delivery(Delivery&& src) noexcept
{
    copy(src);
    src._numItems = 0;
    src._maxSize = 0;
    delete[] src.deliveryItems;
    src.deliveryItems = nullptr;
}

Delivery& Delivery::operator=(Delivery&& src) noexcept
        {
    if (this == &src) return *this;
    copy(src);
    src._numItems = 0;
    src._maxSize = 0;
    delete[] src.deliveryItems;
    src.deliveryItems = nullptr;
    return *this;
}

int Delivery::genNameIndex(int maxIndex)
{
    //uniform_int_distribution<int> distro(0, maxIndex);
    return (distroDelivery(mtDelivery) % maxIndex);
}
int Delivery::genClassIndex(int maxIndex)
{
    //uniform_int_distribution<int> distro(0, maxIndex);
    return (distroDelivery(mtDelivery) % maxIndex);
}
int Delivery::genStorageMethodIndex(int maxIndex)
{
    //uniform_int_distribution<int> distro(0, maxIndex);
    return (distroDelivery(mtDelivery) % maxIndex);
}

double Delivery::genCost(double minCost, double maxCost)
{
    //uniform_real_distribution<double> distro(minCost, maxCost);
    return (fmod(distroDoubleDelivery(mtDelivery), maxCost) + minCost);
}
int Delivery::genAmount(int maxAmount)
{
    //uniform_int_distribution<int> distro(0, maxAmount);
    return (distroDelivery(mtDelivery) % maxAmount);
}

int Delivery::genMaxTime(int maxMaxTime)
{
    //uniform_real_distribution<float> distro(0, maxMaxTime);
    return (distroDelivery(mtDelivery) % maxMaxTime);
}


Delivery::~Delivery()
{
    //cout << "in destructor" << endl;
    delete[] deliveryItems;
}


//Precondition:
//Postcondition:
Produce Delivery::makeProduce(double minCost = 0.0) {
    //cout << "in makeProduce" << endl;
    double MAX_COST = 100.00;
    int MAX_AMOUNT = 100;
    int MAX_TIME = 500;
    string names[] = {"Potato", "Onion", "Winter Squash", "Garlic", "Apple", "Cilantro",
                      "Blueberry", "Zucchini", "Apricot", "Chantrelle Mushrooms", "Banana",
                      "Thyme", "Oyster Mushroom"};
    string classifications[] = {"Fruit", "Vegetable", "Fungus", "Herb"};
    string storageReqs[] = {"dark", "counter", "refrigerate"};
    //cout << (*(&names+1)-names) << endl;
    int namesIndex = genNameIndex(int(*(&names+1)-names-1));
    int classIndex = genClassIndex(int(*(&classifications+1)-classifications-1));
    int storageReqsIndex = genStorageMethodIndex(int(*(&storageReqs+1)-storageReqs-1));
    double cost = genCost(minCost, MAX_COST);
    double amount = genAmount(MAX_AMOUNT);
    int maxTime = genMaxTime(MAX_TIME);
    //cout << "just stuff. food: " << namesIndex << " storageMethod: " << storageReqsIndex << " expirationDate:" << maxTime << endl;
    Produce p = Produce(names[namesIndex], classifications[classIndex], cost, amount,
                           storageReqs[storageReqsIndex], maxTime);
    //cout << "op= successful" << endl;
    return p;
}

Produce* Delivery::expand(Produce *arr)
{
    //cout << "in expand" << endl;
    _maxSize *= 2;
    Produce* newArr = new Produce[_maxSize];

    for (int i = 0; i < _numItems; i++)
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    newArr = nullptr;
    return arr;
    cout << "expansion complete" << endl;
}

//Precondition:
//Postcondition:
//delivery items created independently of food array
Produce* Delivery::forecastDelivery(int minPrice)
{
    //cout << "in forecast delivery" << endl;
    int totalPrice = 0;
    Produce* newProduce = new Produce[_maxSize];
    while (totalPrice < minPrice) {
        if (_numItems >= _maxSize) newProduce = expand(newProduce);
        //cout << "num items: " << _numItems << " maxSize: " << _maxSize << endl;
        newProduce[_numItems] = makeProduce();
        //cout << "out of makeProduce" << endl;
        totalPrice += newProduce[_numItems].getCost();
        _numItems++;
    }
    //cout << "forecastDelivery complete" << endl;
    return newProduce;
}

//Precondition:
//Postcondition:
//move semantics used to transfer ownership of newProduce array to deliveryItems
void Delivery::fillBox(Produce* newProduce)
{
    //cout << "in fillBox" << endl;
    deliveryItems = new Produce[_numItems];
    for (int i = 0; i < _numItems; i++)
    {
        //cout << "in fillBox loop" << endl;
        deliveryItems[i] = newProduce[i];
    }
}

//Precondition:
//Postcondition:
void Delivery::replaceItem(int itemIndex)
{
    //cout << "in replaceItem" << endl;
    double minCost = deliveryItems[itemIndex].getCost();
    deliveryItems[itemIndex] = makeProduce(minCost);
}

//Precondition:
//Postcondition:
void Delivery::deliverBox(int currTime)
{
    //cout << "in deliverBox" << endl;
    for (int i = 0; i < _numItems; i++)
    {
        if(deliveryItems[i].checkExpired(currTime))
        {
            replaceItem(i);
        }
    }
}

//Precondition:
//Postcondition:
string Delivery::shareOrder()
{
    //cout << "in shareOrder" << endl;
    string report;
    double sum = 0;
    for (int i = 0; i < _numItems; i++)
    {
        report += deliveryItems[i].getName() + "-" + to_string(deliveryItems[i].getExpirationDate()) + "\n";
        sum += deliveryItems[i].getCost();
    }
    report += "total cost: " + to_string(sum) + "\n";
    return report;
}





