QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RESOURCES += resources.qrc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/FileCPP/dbcontroller.cpp \
    Model/FileCPP/Utenti.cpp \
    Model/FileCPP/Item.cpp \
    Model/FileCPP/Casa.cpp \
    Model/FileCPP/Cibo.cpp \
    Model/FileCPP/Libri.cpp \
    Model/FileCPP/Trasporto.cpp \
    Model/FileCPP/Vestiti.cpp \
    Database/database.cpp \
    View/FileCPP/aggiungiItem.cpp \
    View/FileCPP/carrello.cpp \
    View/FileCPP/home.cpp \
    View/FileCPP/login.cpp \
    View/FileCPP/main.cpp \
    View/FileCPP/loginForm.cpp \
    View/FileCPP/profile.cpp \
    View/FileCPP/registrazione.cpp\
    View/FileCPP/hamburgermenu.cpp\
    View/FileCPP/modificaItem.cpp\
    View/FileCPP/itemWidget.cpp\
    View/FileCPP/VisitorItem.cpp\
    View/FileCPP/scrollWidget.cpp

HEADERS += \
    Controller/FileH/dbcontroller.h \
    Model/FileH/Utenti.h \
    Model/FileH/Item.h \
    Model/FileH/DoubleList.h \
    Model/FileH/Casa.h \
    Model/FileH/Cibo.h \
    Model/FileH/Libri.h \
    Model/FileH/Trasporto.h \
    Model/FileH/Vestiti.h \
    Model/FileH/VisitorItemInterface.h \
    Database/database.h \
    View/FileH/aggiungiItem.h \
    View/FileH/carrello.h \
    View/FileH/home.h \
    View/FileH/login.h \
    View/FileH/loginForm.h \
    View/FileH/profile.h \
    View/FileH/registrazione.h\
    View/FileH/hamburgermenu.h\
    View/FileH/modificaItem.h\
    View/FileH/itemWidget.h\
    View/FileH/VisitorItem.h\
    View/FileH/scrollWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
