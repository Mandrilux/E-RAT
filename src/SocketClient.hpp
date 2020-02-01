#pragma once

#include <thread>
#include <memory>
#include <queue>
#include "Message.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


class	SocketClient
{
public:
	SocketClient(int fd, sockaddr_in client_addr);
	~SocketClient();

	void start();
	void close();
	void stop();

	void	addMessage(const ERat::Message& message);
	bool	isOnline() const;

	std::string const&	getIp() const;

private:
	void loop();

private:
	int	_fd;
	std::unique_ptr<std::thread>	_thread;
	bool	_running;
	std::queue<ERat::Message>	_messageList;
	std::string	_ip;
};