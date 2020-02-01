#include "SocketServer.hpp"

SocketServer::SocketServer(int port)
{
  this->_port = port;
}

SocketServer::~SocketServer()
{
}


void SocketServer::run()
{
  this->_mastersocket = socket(AF_INET , SOCK_STREAM , 0);
  if(this->_mastersocket == INVALID_SOCKET)
  {
    //  perror("socket()");
      exit(0);
  }

  std::cout << "Socket created" << std::endl;

  /*

  sockaddr_in sin = { 0 };

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);

  if(bind (this->_mastersocket, (sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
  {
      //perror("bind()");
      exit(errno);
  }

  puts("bind done");

  if(listen(this->_mastersocket, 32) == SOCKET_ERROR)
  {
    //  perror("listen()");
      exit(errno);
  }

  puts("Listening");*/

}
