#include <iostream>
#include <string>
#include "../FileH/Item.h"
using namespace std;



Item::Item(){

}

Item:: Item( string n, string d, double p,int i, int q): name(n), desc(d), price(p), ID(i), quantity(q){

}

int Item::getID()const{return ID;}

string Item:: getName()const {return name;}
void Item::setName(string n) {name=n;}

string Item:: getDesc()const {return desc;}
void Item::setDesc(string d){desc=d;}

double Item:: getPrice()const {return price;}
void Item::setPrice(double p){price=p;}

int Item:: getQuantity()const {return quantity;}
void Item::setQuantity(int q){quantity=q;}


void Item::toString(ostream& os)const{
    os << "Nome: " << name<< endl;
    os << "Descrizione: " << desc<< endl;
    os << "Prezzo: " << price<< endl;
    os << "Quantità: " << quantity<< endl;
    os << "ID: " << ID<< endl;
}

bool Item::operator==(const Item& it) const{
    return ID == it.getID();
}

std::ostream& operator<<(ostream& os, const Item& item){
    item.toString(os);
        return os;
}

void Item::accept(VisitorItemInterface& )
{

}


Item::~Item(){delete this;}



