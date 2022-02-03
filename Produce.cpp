/*
 *  Implementation Invariant (explanation of design choices)
 *  - Move semantics supported
 *  - Copy construction/assignment supported
 *
 *  copy(const Produce& src)
 *  - helper function for copying attributes of produce objects. used for copy constructors/move semantics.
 *  zeroOut(Produce& src)
 *  - helper function that sets all of src's attributes to 0/empty strings. used for move semantics.
 *  outage()
 *  - wrapper for spoil()
*/

#include <random>
#include "Produce.h"

//default constructor
Produce::Produce()
{
    _name = "invalid_name";
    _classification = "invalid_class";
    _cost = -1;
    _amount = -1;
    _storageReqs = "invalid_storage_reqs";
    _expired = false;
    _expirationDate = -1;
    _storageMethod = "invalid_storage_method";
    _maxTime = -1;
    _currTime = -1;
}

//Parameterized Constructor
Produce::Produce(const ProduceInput& info)
{
    const int IMPROPER_DARK_TIME = 24;
    const int IMPROPER_REFRIGERATOR_TIME = 1;
    const string DARK = "dark";
    const string REFRIGERATOR = "refrigerator";
    _name = info.name;
    _classification = info.classification;
    _cost = info.cost;
    _amount = info.amount;
    _storageReqs = info.storageReqs;
    _storageMethod = info.storageMeth;
    _maxTime = info.maxTime;
    _currTime = 0;
    if (info.storageMeth == DARK) _expirationDate = IMPROPER_DARK_TIME;
    else if (info.storageMeth == REFRIGERATOR) _expirationDate = IMPROPER_REFRIGERATOR_TIME;
    else _expirationDate = info.maxTime;
}

//Precondition: src, a Produce object
//Postcondition: attributes of src are copied to this Produce object
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

//Precondition: src, a Produce object
//Postcondition: the attributes of src are set to 0 or empty strings
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

//Copy constructor
Produce::Produce(const Produce& src)
{
    copy(src);
}

//Overloaded assignment operator
Produce& Produce::operator=(const Produce& src)
{
    if (this == &src) return *this;
    copy(src);
    return *this;
}

//Move constructor
Produce::Produce(Produce&& src) noexcept
{
    copy(src);
    zeroOut(src);
}

//Move assignment operator
Produce& Produce::operator=(Produce&& src) noexcept
        {
            if (this == &src) return *this;
            copy(src);
            zeroOut(src);
            return *this;
        }

//Precondition: None
//Postcondition: returns _cost
double Produce::getCost() const { return _cost; }

//Precondition: None
//Postcondition: sets _expired to true, returns true
bool Produce::spoil() {
    _expired = true;
    return true;
}

//Precondition: none
//Postcondition: sets _expired to true, returns true
bool Produce::outage()
{
    return spoil();
}

//Precondition: currTime, the time used to compare against the expiration date
//Postcondition: _expired possibly updated, returns value of _expired
 bool Produce::checkExpired(int currTime)
{
    _currTime = currTime;
    if (currTime >= _maxTime) return spoil();
    if (currTime >= _expirationDate) return spoil();
    return _expired;
}

//Precondition: None
//Postcondition: returns string with summary of Produce object's attributes
string Produce::query()
{
    string report = "Name: " + _name + ". Class: " + _classification + ". Price: " + to_string(_cost) +
            ". Expired: " + to_string(_expired) + ". Expiration time: " + to_string(_expirationDate)
            + " hours. \n";
    return report;
}


