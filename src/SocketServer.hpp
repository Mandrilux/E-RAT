#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <stdlib.h>
#include <iostream>
#define EXIT_SUCESS 1
#ifdef WIN32 /* si Windows */

#include <winsock2.h>

#else /* si Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

class SocketServer
{
    public:
        SocketServer(int port);
        void	run();
        void loop();
        bool loopOne(std::function<bool(SOCKET)> func);
        void close();
        ~SocketServer();

    protected:
        SOCKET _mastersocket;
        int _port;
};


#endif //HTTP_SERVER_SOCKET_H
