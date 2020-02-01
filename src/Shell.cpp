#include "Shell.hpp"

#include <iostream>
#include <string>
#include "String.hpp"

namespace ERat
{
	Shell::Shell()
	{

	}

	bool	Shell::initialize()
	{
		_map.insert(std::make_pair("cmd", std::bind(&ERat::Shell::executeCommand, this, std::placeholders::_1)));
		_map.insert(std::make_pair("list", std::bind(&ERat::Shell::listClients, this, std::placeholders::_1)));
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
			std::cout << "> ";
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
			std::cout << "Calling execute command with: " << commandLine << std::endl;
		}
		return true;
	}

	bool	Shell::listClients(std::list<cpp::String> const&)
	{
		std::cout << "Connected clients list:" << std::endl;
		return true;
	}

	Shell::~Shell() = default;
}

