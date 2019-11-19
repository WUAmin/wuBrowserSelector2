#ifndef WUBSBROWSER_H
#define WUBSBROWSER_H

#include <QObject>

struct WuBSBrowser {
    int id;
    QString title;
    QString exec;
    QString args;
    QString icon;
    int size;
};

#endif // WUBSBROWSER_H

