/*
 * Class Invariant
 * The purpose of this class is to model deliveries put together by a produce delivery service. Deliveries have a
 * variable number of Produce items in the array deliveryList. Once Delivery objects are initialized, the client can
 * call deliverBox(currTime) to "deliver" the box, at which point any produce that expired before the delivery time
 * currTime will be replaced with nonspoiled produce. In addition, the class can query information about the delivery
 * or the cost of the delivery.
 *
 * Interface Invariant
 * Delivery()
 * -  default constructor that is not meant to be used. If it is used, the class will not work properly
 * Delivery(int minPrice)
 * - parameterized constructor meant to be used. Initializes the object and adds the generated Produce to it
 * getTotalCost()
 * - getter function for _totalCost
 * shareOrder()
 * - returns a string with information about all the produce items in the Delivery
 * deliverBox(int currTime)
 * - checks if each item in deliveryList will be expired at the time of delivery (currTime). If they are/will be
 *   expired, they are replaced.
 * copy(const Produce& src)
 * - copies src to this object
 *
 */

#include <iostream>
#include "Produce.h"

using namespace std;
#ifndef P2_DELIVERY_H
#define P2_DELIVERY_H


class Delivery {
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
    Produce* forecastDelivery(int minPrice);
    void fillBox(Produce* newProduce);
    void replaceItem(int itemIndex, int currTime);
    static Produce makeProduce(double minCost, int currTime);

public:
    Delivery();
    Delivery(int minPrice);
    Delivery(const Delivery& src);
    Delivery& operator=(Delivery& src);
    Delivery(Delivery&& src) noexcept;
    Delivery& operator=(Delivery&& src) noexcept;
    void copy(const Delivery& src);
    ~Delivery();
    void deliverBox(int currTime);
    string shareOrder();
    [[nodiscard]] double getTotalCost() const;
};


#endif //P2_DELIVERY_H
