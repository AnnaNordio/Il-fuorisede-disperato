
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "Item.h"
/*#include "Model/FileH/Casa.h"
#include "Model/FileH/Cibo.h"
#include "Model/FileH/Libri.h"
#include "Model/FileH/Trasporto.h"
#include "Model/FileH/Vestiti.h"*/

template<class T>
class DoubleList {
private:
    class nodo {
    public:
        T info;
        nodo *prev, *next;
        // convertitore da const T& => nodo
        nodo(const T& i, nodo* p =0, nodo* n =0): info(i), prev(p), next(n) {}
        // distruttore in versione standard
    };
    nodo* first;
    nodo* last;
    // dList vuota iff first == nullptr == last

    static void destroy(nodo* f){
        if(f) {
            destroy(f->next);
            delete f;
        }
    }

    static void copy(nodo* fst, nodo*& f, nodo*& l){
        if(fst==nullptr) {f=l=nullptr; return;}
        // lista non vuota
        nodo* ptr = fst;
        l=f=new nodo(ptr->info,nullptr,nullptr);
        while(ptr->next !=nullptr) {
            ptr = ptr->next;
            l->next = new nodo(ptr->info,l,nullptr);
            l=l->next;
        }
    }

    static bool lex_compare(nodo* f, nodo* s){
        if(!s) return false;
        // s
        if(!f) return true;
        // f & s
        if(f->info < s->info) return true;
        if(s->info < f->info) return false;
        return f->info == s->info && lex_compare(f->next,s->next);
    }

public:

    DoubleList() : first(nullptr), last(nullptr) {}

    DoubleList( const T& t): first(nullptr), last(nullptr) {
        insertFront(t);
    }

    DoubleList(const DoubleList& d): first(nullptr), last(nullptr) {
        copy(d.first,first,last);
    }

    DoubleList& operator=(const DoubleList& d){
        if(this != &d) {
            destroy(first);
            copy(d.first,first,last);
        }
        return *this;
    }

    ~DoubleList(){
        if(first)
            destroy(first);
    }

    void insertFront(const T& t){
        first = new nodo(t,nullptr,first);
        if(last==nullptr) last=first;
        if(first->next != nullptr) (first->next)->prev = first;
    }

    void insertBack(const T& t){
        if(last){ // lista non vuota
            last = new nodo(t,last,nullptr);
            (last->prev)->next=last;
        }
        else // lista vuota
            first=last=new nodo(t);
    }

    void remove(const T& value){
        nodo *current = first;
        while (current != nullptr) {
            if (current->info == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    first = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    last = current->prev;
                }

                nodo *toDelete = current;
                current = current->next;
                delete toDelete;
                return;  // Usciamo dalla funzione dopo la rimozione
            }
            current = current->next;
        }
    }

    void print() const {
        nodo* current = first;
        while (current != nullptr) {
            current->info->toString(std::cout);
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool operator<(const DoubleList& d) const{
        return lex_compare(first,d.first);
    }

    void concat(const DoubleList<T>& otherList) {
        if (otherList.first) {  // Verifica se l'altra lista non è vuota
            if (!first) {  // Se la lista corrente è vuota, copia semplicemente l'altra lista
                copy(otherList.first, first, last);
            } else {
                // Altrimenti, collega l'ultimo nodo della lista corrente al primo nodo dell'altra lista
                last->next = otherList.first;
                otherList.first->prev = last;
                // Aggiorna il puntatore all'ultimo nodo
                last = otherList.last;
            }
        }
    }


    class const_iterator {
        friend class DoubleList<T>;
    private:
        const nodo* ptr;
        bool pastTheEnd;
        // iteratore indefinito IFF ptr == nullptr & pastTheEnd==false
        const_iterator(const nodo* p, bool pte=false): ptr(p), pastTheEnd(pte) {}
    public:

        const_iterator(): ptr(nullptr), pastTheEnd(false) {}

        const_iterator& operator++() {
            // const_iterator indefinito: nulla da fare
            // ptr == 0 & pte=ff
            // const_iterator pastTheEnd: nulla da fare
            // pte=tt
            if(ptr && !pastTheEnd ) {
                if(ptr->next==nullptr) {ptr = ptr+1; pastTheEnd=true;}
                else ptr = ptr->next;
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp(*this);
            if(ptr && !pastTheEnd ) {
                if(ptr->next==nullptr) {ptr += 1; pastTheEnd=true;}
                else ptr = ptr->next;
            }
            return tmp;
        }

        const_iterator& operator--() {
            if(ptr) {
                if(pastTheEnd==true) {ptr = ptr-1; pastTheEnd=false;}
                    // const_iteratore si riferisce al primo elemento
                else if(ptr->prev==nullptr) ptr=nullptr;
                else ptr=ptr->prev;
            }
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp(*this);
            if(ptr) {
                if(ptr->prev==nullptr) ptr=nullptr;
                else if(pastTheEnd==true) {ptr = ptr-1; pastTheEnd=false;}
                else ptr=ptr->prev;
            }
            return tmp;
        }

        const T&  operator*() const {
            return ptr->info;
        }

        const T*  operator->() const {
            return &(ptr->info);
        }

        bool operator==(const const_iterator& cit) const {
            return ptr == cit.ptr;
        }

        bool operator!=(const const_iterator& cit) const {
            return ptr != cit.ptr;
        }
    };

    const_iterator begin() const {
        if(first != nullptr) return const_iterator(first);
        return const_iterator();
    }

    const_iterator end() const {
        if(first == nullptr) return const_iterator();
        return const_iterator(last+1,true);
    }

    const_iterator search(const T& value) const {
        nodo* current = first;
        while (current != nullptr) {
            if (current->info == value) {
                return const_iterator(current);
            }
            current = current->next;
        }
        return end();
    }

};
#endif //DOUBLELIST_H
