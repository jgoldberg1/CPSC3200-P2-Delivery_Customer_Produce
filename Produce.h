/*
 * Class Invariant
 *   The purpose of this class is to simulate produce items. Produce objects represent a group of the same type of
 * produce that was bought at the same time. The main client interaction with the class involves the tracking of
 * expiration and expiration dates. The client can check the expiration date, record that there has been a power outage,
 * or mark an object as spoiled.
 *
 * Interface Invariant
 * getCost()
 * - getter function for the _cost attribute
 * spoil()
 * - marks an object as expired
 * checkExpired(int currTime)
 * - checks whether the object is expired at currTime
 * query()
 * - returns a summary of the Produce object
 * outage()
 * - marks an object as expired. User can call this to show that there has been an outage.
 */
#include <iostream>
#include <cctype>
#include <random>
using namespace std;
#ifndef P2_PRODUCE_H
#define P2_PRODUCE_H

struct ProduceInput {
    string name;
    string classification;
    double cost;
    double amount;
    string storageReqs;
    string storageMeth;
    int maxTime;
};

class Produce {
private:
    string _name = "invalid_name";
    string _classification = "invalid_class";
    double _cost = -1;
    double _amount = -1;
    string _storageReqs = "invalid_storage_reqs";
    bool _expired = false;
    int _expirationDate = -1;
    string _storageMethod = "invalid_storage_method";
    int _maxTime = -1;
    int _currTime = -1;
    void copy(const Produce& src);
    void zeroOut(Produce& src);

public:
    Produce(const Produce& src);
    Produce& operator=(const Produce& src);
    Produce& operator=(Produce&& src) noexcept;
    Produce(Produce&& src) noexcept;
    Produce();
    Produce(const ProduceInput& info);
    double getCost() const;
    bool spoil();
    bool outage();
    bool checkExpired(int currTime);
    string query();
};


#endif //P2_PRODUCE_H
