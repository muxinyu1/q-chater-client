#include "chatwindow.h"
#include "mainwindow.h"
#include "friendcard.h"

#include <QApplication>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
