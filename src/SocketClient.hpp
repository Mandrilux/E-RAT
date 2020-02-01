#pragma once

#include <thread>
#include <memory>
#include <queue>
#include "Message.h"

class	SocketClient
{
public:
	SocketClient(int fd);
	~SocketClient();

	void start();
	void close();
	void stop();

private:
	void loop();

private:
	int	_fd;
	std::unique_ptr<std::thread>	_thread;
	bool	_running;
	std::queue<ERat::Message>	_messageList;
};