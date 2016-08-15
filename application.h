#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include "mainwindow.h"
#include "networkio.h"
#include <thread>
class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int argc, char** argv);


signals:
public slots:

private:
    MainWindow window;
    ads_bridge::NetworkIO* pNetworkIO;
};

#endif // APPLICATION_H
