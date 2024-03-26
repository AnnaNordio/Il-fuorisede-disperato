#include "../FileH/login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.resize(600,512);
    w.show();
    return a.exec();
}
