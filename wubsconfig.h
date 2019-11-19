#ifndef WUBSCONFIG_H
#define WUBSCONFIG_H

#include <QObject>
#include <wubsbrowser.h>

class WuBSConfig : public QObject
{
    Q_OBJECT
    void saveJson(QJsonDocument document, QString fileName);
public:
    explicit WuBSConfig(QObject *parent = nullptr);
    double configVersion;
    QList<WuBSBrowser> browsers;
    bool readConfig(QString configPath);

signals:

public slots:
};



#endif // WUBSCONFIG_H
