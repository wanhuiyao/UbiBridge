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
    void start();

    void waitForConnection();

signals:
public slots:

private:
    MainWindow window;
    NetworkIO networkIO;
};

#endif // APPLICATION_H
