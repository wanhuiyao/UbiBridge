#include "application.h"
#include <chrono>
#include <iostream>
Application::Application(int argc, char** argv)
    : QApplication(argc, argv)
{
    window.setGeometry (100, 100, 800, 600);
    window.show ();
}

void Application::start(){
    std::thread connectionThread(&Application::waitForConnection, this);
    connectionThread.detach ();
}

void Application::waitForConnection(){
    while(true){
        std::cout << "waiting for connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


