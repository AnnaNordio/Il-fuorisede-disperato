#if !defined(CIBO_H)
#define CIBO_H

#include <iostream>
#include "Item.h"

using namespace std;

class Cibo: public Item{
    private:
        string genere;
    public:
        Cibo();
        Cibo(string n, string d, double p, string g, int id, int quantità);

        string getGenere()const;
        void setGenere(string g);
        void toString(ostream& os) const;
        void accept(VisitorItemInterface& visitor);
        virtual ~Cibo();

};
#endif

