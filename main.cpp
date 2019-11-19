#include "mainwindow.h"
#include <QApplication>
#include <wubsconfig.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WuBSConfig appConfig;
//    QString strArgs = "";
//    for (int i = 1; i < QCoreApplication::arguments().length(); i++) {
//        strArgs += "'" + QCoreApplication::arguments()[i] + "' ";
//    }
//    strArgs = strArgs.trimmed();
    qDebug() << QCoreApplication::arguments().mid(1).join(' ');
    // qDebug() << strArgs;
    MainWindow w(&appConfig, QCoreApplication::arguments().mid(1).join(' '));
    //MainWindow w(&appConfig, strArgs);
    w.show();

    return a.exec();
}
