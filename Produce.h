//
// Created by jenma on 1/15/2022.
//
#include <iostream>
#include <cctype>
#include <random>
using namespace std;
#ifndef P2_PRODUCE_H
#define P2_PRODUCE_H


class Produce {
private:
    int IMPROPER_REFRIGERATE_TIME = 1;
    int IMPROPER_DARK_TIME = 24;
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

    //methods
public:
    struct input {
        string name = "invalid_name";
        string classification = "invalid_classification";
        double cost = -1;
        double amount = -1;
        string storageReqs = "invalid_storage_reqs";
        int maxTime = -1;
    };
    void copy(const Produce& src);
    void zeroOut(Produce& src);
    Produce(const Produce& src);
    Produce& operator=(const Produce& src);
    Produce& operator=(Produce&& src) noexcept;
    Produce(Produce&& src) noexcept;
    Produce();
    Produce(string name, string classification, double cost, double amount, string storageReqs, int maxTime);
    string getName();
    string getClass();
    const double getCost();
    const double getAmount();
    string getStorageReqs();
    int getExpirationDate();
    string getStorageMethod();
    bool spoil();
    bool outage();
    bool checkExpired(int currTime);
};


#endif //P2_PRODUCE_H
