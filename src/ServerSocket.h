#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#ifdef WIN32 /* si vous êtes sous Windows */

#include <winsock2.h>

#else /* si vous êtes sous Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

class SocketServer
{
    public:
        SocketServer(int port);
        ~SocketServer();

    protected:
        SOCKET mastersocket;
};


#endif //HTTP_SERVER_SOCKET_H
