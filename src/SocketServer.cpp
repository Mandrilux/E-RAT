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
      perror("socket()");
      exit(0);
  }

  std::cout << "Socket created" << std::endl;

  sockaddr_in sin = { 0 };

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);

  if(bind(_mastersocket, (sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
  {
      perror("bind()");
      exit(errno);
  }

  std::cout << "bind [OK]" << std::endl;

  if(listen(_mastersocket, 32) == SOCKET_ERROR)
  {
      perror("listen()");
      exit(errno);
  }

  std::cout << "LISTENING [OK]" << std::endl;

}


void SocketServer::close()
{
  ::close(_mastersocket);
}

void  SocketServer::loop()
{
    sockaddr_in csin = { 0 };
    unsigned int sinsize = sizeof csin;
    SOCKET csock_tmp;

    while ((csock_tmp = accept(_mastersocket, (sockaddr *)&csin, &sinsize)))
    {
		auto client = std::make_shared<SocketClient>(csock_tmp);

		client->start();

		_clients.push_back(client);
    }
}
