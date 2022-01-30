//
// Created by jenma on 1/15/2022.
//

#include <cmath>
#include <random>
#include "Produce.h"



Produce::Produce() = default;

Produce::Produce(string name, string classification, double cost, double amount, string storageReqs, int maxTime)
{
    _name = name;
    _classification = classification;
    _cost = cost;
    _amount = amount;
    _storageReqs = storageReqs;
    _storageMethod = storageReqs;
    _expirationDate = maxTime;
    _maxTime = maxTime;
    _currTime = 0;
}

//copy function
void Produce::copy(const Produce &src) {
    _name = src._name;
    _classification = src._classification;
    _cost = src._cost;
    _amount = src._amount;
    _storageReqs = src._storageReqs;
    _storageMethod = src._storageMethod;
    _expirationDate = src._expirationDate;
    _maxTime = src._maxTime;
    _currTime = src._currTime;
}

void Produce::zeroOut(Produce& src)
{
    src._name = "";
    src._classification = "";
    src._cost = 0;
    src._amount = 0;
    src._storageReqs = "";
    src._storageMethod = "";
    src._expirationDate = 0;
    src._maxTime = 0;
    src._currTime = 0;
}

Produce::Produce(const Produce& src)
{
    copy(src);
}

Produce& Produce::operator=(const Produce& src)
{
    if (this == &src) return *this;
    copy(src);
    return *this;
}

//how do move assignment constructors work?????
//you copy and then set all of src's attributes to 0?
//...why does this work?
Produce::Produce(Produce&& src) noexcept
{
    copy(src);
    zeroOut(src);
}

Produce& Produce::operator=(Produce&& src) noexcept
        {
            if (this == &src) return *this;
            //MAYBE I NEED TO DELETE THINGS??
            copy(src);
            zeroOut(src);
            return *this;
        }

string Produce::getName() { return _name; }

string Produce::getClass() { return _classification; }

const double Produce::getCost() { return _cost; }

const double Produce::getAmount() { return _amount; }

string Produce::getStorageReqs() { return _storageReqs; }

int Produce::getExpirationDate() { return _expirationDate; }

string Produce::getStorageMethod() { return _storageMethod; }

bool Produce::spoil() {
    _expired = true;
    return true;
}

bool Produce::outage()
{
    return spoil();
}

//got rid of outage stuff!! make sure to document those changes
 bool Produce::checkExpired(int currTime)
{
    _currTime = currTime;
    if (currTime >= _maxTime) return spoil();
    if (currTime >= _expirationDate) return spoil();
    return _expired;
}


