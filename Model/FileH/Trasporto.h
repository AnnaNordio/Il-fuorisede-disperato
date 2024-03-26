#if !defined(TRASPORTO_H)
#define TRASPORTO_H

#include <iostream>
#include "Item.h"

using namespace std;

class Trasporto: public Item{
    private:
    std::string durata;
    public:
        Trasporto();
        Trasporto(string n, string d, double p, string du, int id, int quantità);

        string getDurata()const;
        void setDurata(string du);
        void accept(VisitorItemInterface& visitor);
        void toString(ostream& os) const;

        virtual ~Trasporto();
};
#endif

