#ifndef VISITORITEM_H
#define VISITORITEM_H
#include "../../Model/FileH/VisitorItemInterface.h"
#include <QWidget>
#include "../../Model/FileH/Casa.h"
#include "../../Model/FileH/Cibo.h"
#include "../../Model/FileH/Libri.h"
#include "../../Model/FileH/Trasporto.h"
#include "../../Model/FileH/Vestiti.h"

class VisitorItem: public VisitorItemInterface{
private:
    QWidget* widget;
public:
    QWidget* getWidget() const;
    void visitCasa(Casa& casa);
    void visitCibo(Cibo& cibo);
    void visitLibri(Libri& libro);
    void visitTrasporto(Trasporto& trasporto);
    void visitVestiti(Vestiti& vestito);
};

#endif // VISITORITEM_H
