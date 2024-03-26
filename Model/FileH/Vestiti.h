#if !defined(VESTITI_H)
#define VESTITI_H

#include <iostream>
#include "Item.h"

using namespace std;

class Vestiti: public Item{
    private:
        string genere;
        string taglia;
        string colore;
    public:
        Vestiti();
        Vestiti(string n, string d, double p, string g, string t, string c, int id, int quantità);

        string getGenere()const;
        void setGenere(string g);

        string getTaglia()const;
        void setTaglia(string t);

        string getColore()const;
        void setColore(string c);
        void accept(VisitorItemInterface& visitor);
        void toString(ostream& os) const;

        virtual ~Vestiti();

};
#endif

