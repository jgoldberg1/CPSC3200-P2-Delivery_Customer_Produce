/* Jenna Goldberg
 * 2/2/2022
 * PA2
 * P2.cpp, Produce.cpp, Produce.h, Delivery.cpp, Delivery.h, Customer.cpp, Customer.h
 *
 *This project simulates Produce, Delivery, and Customers. Customers order Deliveries of Produce from a delivery
 * service. Produce, Delivery, and Customers are all classes. Delivery has-some Produce, and Customers have-a Delivery.
 * Customers can place orders for Deliveries to be delivered at a specific time. Delivery objects randomly generate
 * Produce objects to be composed of. The Delivery object ensures that no Produce objects are expired at the delivery
 * time.
 *
 * The driver tests many aspects of the program. Each class is individually tested. Objects are generated with
 * randomized parameters and all public functionalities are demonstrated. Class interactions are also tested, as classes
 * regularly interact as part of their normal functionality. Finally, several special tests are implemented as per the
 * instructions. Deep copying is tested in testDeepCopy(), using the copy function. Use of STL containers
 * with smart pointers is tested in testContainerStorage().
 *
 */

#include <iostream>
#include <vector>
#include <memory>
#include "Delivery.h"
#include "Produce.h"
#include "Customer.h"

random_device rdMain;
mt19937 mtMain(rdMain());
uniform_int_distribution<int> distroMain(0, RAND_MAX);
uniform_real_distribution<double> distroDoubleMain(0, RAND_MAX);

int genMinPrice()
{
    const int PRICE_MIN = 0;
    const int PRICE_MAX = 500;
    return (distroMain(mtMain) % PRICE_MAX + PRICE_MIN);
}

int genBalance()
{
    const int BALANCE_MIN = 500;
    const int BALANCE_MAX = 5000;
    return (distroMain(mtMain) % BALANCE_MAX + BALANCE_MIN);
}

string genName()
{
    const int INDEX_MAX = 9;
    const int INDEX_MIN = 0;
    const string names[10] = {"Karli Montoya", "Jermaine Roberson", "Bradley Lutz", "Jaylin Mendoza",
                              "Allie Snyder", "Greyson Davis", "Bethany Forbes", "Kallie Frank",
                              "Daniela Howell", "Dustin Kramer"};
    return names[(distroMain(mtMain) % INDEX_MAX + INDEX_MIN)];
}

string genAddress()
{
    const string addresses[10] = {"9379 Ridgeview Ave.", "89 Roehampton Avenue", "941 Border Road",
                                  "53 Lower River Ave.", "281 Wentworth St.", "37 Lafayette Street",
                                  "885 University Court", "78 10th Drive", "41 Carson Rd.",
                                  "42 Southampton St."};
    const int INDEX_MAX = 9;
    const int INDEX_MIN = 0;
    return addresses[(distroMain(mtMain) % INDEX_MAX + INDEX_MIN)];
}

string genProduceName()
{
    const string NAMES[13] = { "Potato", "Onion", "Winter Squash", "Garlic", "Apple",
                               "Cilantro", "Blueberries", "Zucchini", "Apricots",
                               "Chantrelle Mushrooms", "Bananas", "Thyme", "Oyter Mushroom"};
    const int INDEX_MIN = 0;
    const int INDEX_MAX = 12;
    return NAMES[distroMain(mtMain) % INDEX_MAX + INDEX_MIN];
}

string genProduceClass()
{
    const string CLASS[4] = {"Vegetable", "Fruit", "Herb", "Fungus"};
    const int INDEX_MIN = 0;
    const int INDEX_MAX = 3;
    return CLASS[distroMain(mtMain) % INDEX_MAX + INDEX_MIN];
}

string genProduceStorage()
{
    const string CLASS[4] = {"dark", "refrigerate", "counter"};
    const int INDEX_MIN = 0;
    const int INDEX_MAX = 3;
    return CLASS[distroMain(mtMain) % INDEX_MAX + INDEX_MIN];
}

double genCost()
{
    const int MIN_COST = 1;
    const int MAX_COST = 100;
    return fmod(distroDoubleMain(mtMain), MAX_COST) + MIN_COST;
}

double genAmount()
{
    const int MIN_COST = 1;
    const int MAX_COST = 100;
    return fmod(distroDoubleMain(mtMain), MAX_COST) + MIN_COST;
}

int genMaxTime()
{
    const int MIN_TIME = 1;
    const int MAX_TIME = 500;
    return distroMain(mtMain) % MAX_TIME + MIN_TIME;
}




void testDeepCopy()
{
    cout << "Testing deep copying. If the last two order summaries are identical, deep copying was successful." << endl;
    unique_ptr<Delivery> subj = make_unique<Delivery>(genMinPrice());
    cout << subj->shareOrder() << endl;
    unique_ptr<Delivery> src = make_unique<Delivery>(genMinPrice());
    cout << src->shareOrder() << endl;
    subj->copy(*src);
    cout << subj->shareOrder() << endl;
}

void testContainerStorage()
{
    cout << "Testing STL container storage." << endl;
    const int V_SIZE = 3;
    vector<shared_ptr<Delivery>> delV;
    cout << "An empty vector of shared_ptrs has been created." << endl;
    for (int i = 0; i < V_SIZE; i++)
    {
        shared_ptr<Delivery> d = make_shared<Delivery>(genMinPrice());
        delV.push_back(d);
    }
    cout << "The vector has been filled with Delivery objects. The vector contains the only references to them:"
    << endl;
    for (int i = 0; i < V_SIZE; i++)
    {
        cout << "Number of refs to element " << i << ": " << delV[i].use_count() << endl;
    }
    cout << "Now new shared_pointers will be created to hold references. There will now be two references per element:"
    << endl;
    for (int i = 0; i < V_SIZE; i++)
    {
        shared_ptr<Delivery> d = delV[i];
        cout << "Number of refs to element " << i << ": " << delV[i].use_count() << endl;
    }
    cout << "Those new references have gone out of scope, so now it is just the vector again:" << endl;
    for (int i = 0; i < V_SIZE; i++)
    {
        cout << "Number of refs to element " << i << ": " << delV[i].use_count() << endl;
    }
    cout << "When this function ends, the vector will go out of scope, there will be no more references, and the "
    << "memory will be deallocated." << endl << endl;
}


void testCustomerClass()
{
    const int MAX_ORDERS = 5;
    const int MIN_ORDERS = 1;
    Customer c = Customer(genName(), genAddress(), genBalance(), genMinPrice());
    cout << "Testing Customer class. \nCustomer generated. Customer Summary: " << endl;
    cout << c.summarize();
    int numOrders = distroMain(mtMain) % MAX_ORDERS + MIN_ORDERS;
    cout << "Placing " << numOrders << " orders." << endl;
    for (int i = 0; i < numOrders; i++)
    {
        c.orderDelivery();
        cout << "Order " << i << " - Summary of goods received: " << endl;
        cout << c.queryDelivery() << endl << endl;
    }
}

void testSpoil(shared_ptr<Produce> p)
{
    const int MAX_TIME = 700;
    int currTime = distroMain(mtMain) % MAX_TIME;
    p->spoil();
    cout << "You marked the food as spoiled. The _expired attribute's value is "
         << p->checkExpired(currTime) << endl;
}

void testOutage(shared_ptr<Produce> p)
{
    const int MAX_TIME = 700;
    int currTime = distroMain(mtMain) % MAX_TIME;
    p->outage();
    cout << "You marked that there was a power outage. The _expired attribute's value is "
         << p->checkExpired(currTime) << endl;
}

void testCheckExpired(shared_ptr<Produce> p)
{
    const int MAX_TIME = 700;
    int currTime = distroMain(mtMain) % MAX_TIME;
    p->outage();
    cout << "The current time is " << currTime << ". The _expired attribute's value is "
         << p->checkExpired(currTime) << endl;
}


void runProduceTests(shared_ptr<Produce> p)
{
    const int MAX_CASE = 3;
    for (int i = 0; i <= MAX_CASE; i++)
    {
        //cout << "in runProduceTests loop" << endl;
        int rand = distroMain(mtMain) % MAX_CASE;
        switch (rand) {
            case 0:
                testSpoil(p);
                break;
            case 1:
                testOutage(p);
                break;
            case 2:
                testCheckExpired(p);
                break;
        }
    }
}

void testProduceClass() {
    cout << "Testing Produce class. Making Produce object." << endl;
    ProduceInput pIn = {
            genProduceName(),
            genProduceClass(),
            genCost(),
            genAmount(),
            genProduceStorage(),
            genProduceStorage(),
            genMaxTime()
    };
    shared_ptr<Produce> p = make_shared<Produce>(pIn);
    cout << p->query();
    runProduceTests(p);
    cout << endl;
}

void testDeliveryClass()
{
    cout << "Testing Delivery Class. Generating Delivery object." << endl;
    const int MAX_PRICE = 500;
    const int MAX_TIME = 700;
    int price = distroMain(mtMain) % MAX_PRICE;
    int currTime = distroMain(mtMain) % MAX_TIME;
    unique_ptr<Delivery> d = make_unique<Delivery>(price);
    cout << "Summary of items in Delivery object: \n" << d->shareOrder();
    cout << "Total cost of the items: " << d->getTotalCost() << endl;
    cout << "Delivering the Delivery at " << currTime << " hours. \nThe total price upon delivery might have changed "
         << "if items were replaced due to spoilage. " << endl;
    d->deliverBox(currTime);
    cout << "The new total cost is: " << d->getTotalCost() << endl << endl;
}

int main()
{
    testProduceClass();
    testDeliveryClass();
    testCustomerClass();
    testDeepCopy();
    testContainerStorage();
    return 0;
}