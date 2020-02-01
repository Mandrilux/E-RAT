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
  int enable = 1;
	setsockopt(_mastersocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  std::cout << "[+] Socket" << std::endl;

  sockaddr_in sin = { 0 };

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);

  if(bind(_mastersocket, (sockaddr *) &sin, sizeof sin) == SOCKET_ERROR)
  {
      perror("bind()");
      exit(errno);
  }

  std::cout << "[+] Bind" << std::endl;

  if(listen(_mastersocket, 32) == SOCKET_ERROR)
  {
      perror("listen()");
      exit(errno);
  }
  std::cout << "EPI-RAT Listen " << inet_ntoa(sin.sin_addr) << ":" <<  _port <<  std::endl;
	this->loop();
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

    while ((csock_tmp = accept(_mastersocket, (sockaddr *)&csin, &sinsize)) != -1)
    {
		auto client = std::make_shared<SocketClient>(csock_tmp, csin);

		std::cout << "New client is connected <" << client->getIp() << ">" << std::endl;
		client->start();

		auto it = _clients.begin();

		while (it != _clients.end()) {
			if (!(*it)->isOnline()) {
				it = _clients.erase(it);
			}
			else {
				++it;
			}
		}
		_clients.push_back(client);
    }
}

std::vector<std::shared_ptr<SocketClient> > const&	SocketServer::getClients() const
{
	return _clients;
}
