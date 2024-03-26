#if !defined(CASA_H)
#define CASA_H

#include <iostream>
#include "Item.h"


using namespace std;

class Casa: public Item{
    private:
        string colore;
        string genere;
    public:
        Casa();
        Casa(string n, string d, double p, string c, string g, int id, int quantità);

        string getColore()const;
        void setColore(string c);

        string getGenere()const;
        void setGenere(string g);
        void accept(VisitorItemInterface& visitor);
        void toString(ostream& os) const;


        virtual ~Casa();

};
#endif

