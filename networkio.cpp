#include "networkio.h"
#include <chrono>
#include <iostream>
#include <unistd.h>
using namespace ads_bridge;

NetworkIO::NetworkIO(int port):
    m_port(port){
    if(!createServerSocket ()){
        throw RuntimeException("Failed create server socket");
    }
}

bool NetworkIO::createServerSocket()
{
    m_serverSockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSockFD < 0)
    {
        std::cout << "Cannot create socket." << std::endl;
        return false;
    }

    int on = 1;
    // Allow socket descriptor to be reusable
    if (setsockopt(m_serverSockFD, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)))
    {
        std::cout << "Set socket option failed" << std::endl;
        close(m_serverSockFD);
        m_serverSockFD = -1;
        return false;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(m_port);

    if (bind(m_serverSockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Cannot bind socket to server address." << std::endl;
        close(m_serverSockFD);
        return false;
    }

    if(listen(m_serverSockFD, 10) < 0)
    {
        std::cout << "Listen() failed." << std::endl;
        close(m_serverSockFD);
        return false;
    }

    return true;
}

void NetworkIO::start(){
    m_keepWorking = true;
    std::thread task(&NetworkIO::acceptConnection, this);
    task.detach ();
}

void NetworkIO::acceptConnection (){
    m_isRunning = true;

    int rc;
    //Initialize the master fd_set
    fd_set master_set;
    int max_sd;
    max_sd = m_serverSockFD;
    struct timeval timeout;
    while(m_keepWorking){
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        FD_ZERO(&master_set);
        FD_SET(m_serverSockFD, &master_set);
        rc = select(max_sd + 1, &master_set, NULL, NULL, &timeout);

        if (rc < 0){ // Check to see if the select call failed.
            std::cout << "rc:" << rc << std::endl;
            break;
        }else if (rc == 0){ // Check to see if time out.
            continue;
        }else{  //get a connection
            struct sockaddr_in client_addr;
            unsigned cliengLen = sizeof(client_addr);
            int clientSockFD = accept(m_serverSockFD, (sockaddr *) &client_addr, &cliengLen);
            if (clientSockFD < 0){
                std::cout << "Failed to establish connection to client: FD" << clientSockFD << std::endl;
            }else{
                std::string clientIP = inet_ntoa(client_addr.sin_addr);
                std::cout << "accept connection from:" << clientIP << std::endl;
            }
        }
    }

    m_isRunning = false;
}

void NetworkIO::stop (){
    while(m_isRunning){
        m_keepWorking = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

NetworkIO::~NetworkIO (){

}
