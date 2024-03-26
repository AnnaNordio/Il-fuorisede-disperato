#if !defined(LIBRI_H)
#define LIBRI_H

#include <iostream>
#include "Item.h"

using namespace std;

class Libri: public Item{
    private:
        string isbn;
        string autore;
        string genere;

    public:
        Libri();
        Libri(string n, string d, double p, string i, string a, string g, int id, int quantità);

        string getIsbn()const;
        void setIsbn(string i);

        string getAutore()const;
        void setAutore(string a);

        string getGenere() const;
        void setGenere(string g);
        void accept(VisitorItemInterface& visitor);
        void toString(ostream& os)const;


    virtual ~Libri();


};
#endif

