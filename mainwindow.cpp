#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QGridLayout>
#include <QLabel>
#include <Qt>
#include <QFont>
#include <QtMath>
#include <QProcess>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(WuBSConfig *_appConfig, QString _arg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->appConfig = _appConfig;
    this->arg = _arg;
    ui->setupUi(this);
    this->setWindowTitle(QString("WuBrowserSelector %1").arg(APP_VER));

    foreach(WuBSBrowser wb, appConfig->browsers) {
        QPushButton* pbBrowser = new QPushButton();
        pbBrowser->setProperty("bid", wb.id);
        // Set icon
        pbBrowser->setIcon(QIcon(wb.icon));
        pbBrowser->setIconSize(QSize(wb.size, wb.size));
        // Set Style & Layout
        pbBrowser->setStyleSheet("text-align:left;");
        pbBrowser->setLayout(new QGridLayout());
        // Add label
        QLabel* textLabel = new QLabel(wb.title);
        textLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        textLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        pbBrowser->layout()->addWidget(textLabel);
        // Change Font
        QFont font = textLabel->font();
        font.setPointSize(int(ceil(wb.size / 2.5)));
        textLabel->setFont(font);
        // Connect click signal
        connect(pbBrowser, SIGNAL(clicked()), SLOT(runBrowser()));
        // Add button to window
        ui->vl_browsers->addWidget(pbBrowser);
    }

    this->setStyleSheet("QPushButton {margin: 0px; padding: 8px;} QLabel {margin: 0px; padding: 0px;}");
}

void MainWindow::runBrowser()
{
    qDebug() << "cmd";
    QProcess *process = new QProcess(this);
    QString cmd = '"' + appConfig->browsers[this->sender()->property("bid").toInt()].exec.trimmed() + '"';

    if (appConfig->browsers[this->sender()->property("bid").toInt()].args.trimmed().length() > 1)
        cmd.append(' ' + appConfig->browsers[this->sender()->property("bid").toInt()].args);

    if (this->arg.trimmed().length() > 1)
        cmd.append(' ' + this->arg);
    qDebug() << cmd;
    bool res = process->startDetached(cmd);
    if(!res) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Can not run browser.\n\n" + cmd);
        messageBox.setFixedSize(500,200);
    }
    process->waitForFinished(2000);
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
