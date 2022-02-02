//
// Created by jenma on 1/15/2022.
//
#include <iostream>
#include "Produce.h"

using namespace std;
#ifndef P2_DELIVERY_H
#define P2_DELIVERY_H


class Delivery {
    //attributes
private:
    int _maxSize = 3;
    Produce *deliveryItems;
    int _numItems = 0;
    double _totalCost = 0;
    static int genNameIndex(int maxIndex);
    static int genClassIndex(int maxIndex);
    static int genStorageMethodIndex(int maxIndex);
    static double genCost(double minCost, double maxCost);
    static int genAmount(int maxAmount);
    static int genMaxTime(int currTime, int maxMaxTime);
    Produce* expand(Produce* arr);
    void copy(const Delivery& src);



    //methods
public:
    Delivery();
    Delivery(int minPrice);
    Delivery(const Delivery& src);
    Delivery& operator=(Delivery& src);
    Delivery(Delivery&& src) noexcept;
    Delivery& operator=(Delivery&& src) noexcept;
    ~Delivery();
    Produce* forecastDelivery(int minPrice);
    void fillBox(Produce* newProduce);
    void replaceItem(int itemIndex, int currTime);
    void deliverBox(int currTime);
    string shareOrder();
    Produce makeProduce(double minCost, int currTime);
    [[nodiscard]] int getTotalCost() const;
};


#endif //P2_DELIVERY_H
