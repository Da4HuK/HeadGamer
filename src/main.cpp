#include "UI/MainWindow.hpp"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "main start";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int code = a.exec();
    qDebug() << "main end";
    return code;
}
