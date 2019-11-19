#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wubsconfig.h>
const double APP_VER = 2.5;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(WuBSConfig *_appConfig, QString _arg, QWidget *parent = nullptr);
    ~MainWindow();
    WuBSConfig *appConfig;

private slots:
    void runBrowser();
private:
    Ui::MainWindow *ui;
    QString arg;
};

#endif // MAINWINDOW_H
