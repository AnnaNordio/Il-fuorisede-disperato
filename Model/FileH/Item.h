#if !defined(ITEM_H)
#define ITEM_H

#include <iostream>
#include <string>
#include "VisitorItemInterface.h"
using namespace std;

class Item{
private:
    string name;
    string desc;
    double price;
    int ID;
    int quantity;
public:
    Item();
    Item(string n, string d, double p, int i=-1,  int q=1);
    string getName()const;
    void setName(string n);

    string getDesc()const;
    void setDesc(string n);

    int getID()const;

    double getPrice()const;
    void setPrice(double n);

    int getQuantity()const;
    void setQuantity(int n);



    virtual void accept(VisitorItemInterface& visitor);

    virtual void toString(ostream& os)const;


    bool operator==(const Item& it) const;

    friend std::ostream& operator<<(ostream& os, const Item& item);


    virtual ~Item();
};
#endif

