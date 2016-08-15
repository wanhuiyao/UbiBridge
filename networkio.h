#ifndef NETWORKIO_H
#define NETWORKIO_H


#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "runtimeexception.h"
#include <iostream>

namespace ads_bridge {
    class NetworkIO
    {
    public:
        NetworkIO(int port);
        ~NetworkIO();
        bool createServerSocket();
        void start();   //create a thread waiting for connection
        void stop();    //stop all client connections, stop waiting for connection and close server socket
        void acceptConnection();
    private:
        volatile bool m_keepWorking;
        bool m_isRunning;
        int m_serverSockFD;
        int m_port;
    };
}

#endif // NETWORKIO_H
