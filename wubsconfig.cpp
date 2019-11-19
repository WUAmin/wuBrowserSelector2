#include "wubsconfig.h"
#include <QCoreApplication>
//#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <wubsconfig.h>

WuBSConfig::WuBSConfig(QObject *parent) : QObject(parent)
{
    this->browsers = *new QList<WuBSBrowser>();
    QString configPath = QCoreApplication::applicationDirPath() +  QDir::separator() + "config.json";
    //qDebug() << "config Path: " + configPath;
    if (!readConfig(configPath))
        qFatal("Can not load configs.");
}

bool WuBSConfig::readConfig(QString configPath)
{
    try {
        QFile jFile(configPath);
        jFile.open(QFile::ReadOnly);
        if(!jFile.exists())
            return false;
        QByteArray jData = jFile.readAll();
        if(jData.length() < 3)
            return false;
        QJsonDocument jDoc = QJsonDocument().fromJson(jData);
        QJsonObject jObj = jDoc.object();

        // Load Misc.
        configVersion = jObj["ver"].toDouble();

        // Load browsers
        QJsonArray jBrowsers = jObj["browsers"].toArray();
        int ib = 0;
        foreach(QJsonValue jb, jBrowsers) {
            WuBSBrowser wb;
            wb.id = ib;
            wb.title = jb["title"].toString();
            wb.exec = jb["exec"].toString();
            wb.args = jb["args"].toString();
            wb.icon = jb["icon"].toString();
            wb.size = jb["size"].toInt();
            //qDebug() << "Load" << wb.title << "configs.";
            browsers.append(wb);
            ib++;
        }
        //qDebug() << "Loaded" << browsers.length() << "browsers.";
    } catch(...) {
        return false;
    }

    return true;
}



void WuBSConfig::saveJson(QJsonDocument document, QString fileName) {
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}
