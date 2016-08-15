#include "application.h"
#include <chrono>
#include <iostream>
Application::Application(int argc, char** argv)
    : QApplication(argc, argv)
{
    window.setGeometry (100, 100, 800, 600);
    window.show ();
    pNetworkIO = new ads_bridge::NetworkIO(2020);
    pNetworkIO->start ();
}


