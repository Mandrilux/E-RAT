#include "SocketClient.hpp"

#include <unistd.h>
#include <iostream>

SocketClient::SocketClient(int fd): _fd(fd)
{

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

SocketClient::~SocketClient() {
	this->close();
}