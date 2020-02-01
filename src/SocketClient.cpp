#include "SocketClient.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <unistd.h>
#include <iostream>

SocketClient::SocketClient(int fd, sockaddr_in client_addr): _fd(fd)
{
	_ip = inet_ntoa(client_addr.sin_addr);
}

void	SocketClient::start()
{
	_running = true;
	_thread = std::unique_ptr<std::thread>(new std::thread(&SocketClient::loop, this));
}

void	SocketClient::loop()
{
	while (_running) {
		if (!_messageList.empty())
		{
			auto message = _messageList.front();
			_messageList.pop();

			std::cout << "Encoded: " << message.encodeHeader() << std::endl;;
		}
	}
}

std::string const&	SocketClient::getIp() const {
	return _ip;
}


void	SocketClient::stop() {
	_running = false;
	this->close();
	_thread->join();
}

void	SocketClient::close()
{
	if (_fd != -1) {
		::close(_fd);
		_fd = -1;
	}
}

void	SocketClient::addMessage(const ERat::Message& message)
{
	_messageList.push(message);
}

SocketClient::~SocketClient() {
	this->close();
}