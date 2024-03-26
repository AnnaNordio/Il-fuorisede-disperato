#ifndef VISITORITEMINTERFACE_H
#define VISITORITEMINTERFACE_H

class Casa;
class Cibo;
class Libri;
class Trasporto;
class Vestiti;

class VisitorItemInterface{
    public:
    virtual  ~VisitorItemInterface() = default;
    virtual void visitCasa(Casa& casa)=0;
    virtual void visitCibo(Cibo& casa)=0;
    virtual void visitLibri(Libri& casa)=0;
    virtual void visitTrasporto(Trasporto& casa)=0;
    virtual void visitVestiti(Vestiti& casa)=0;
};
#endif // VISITORITEMINTERFACE_H
