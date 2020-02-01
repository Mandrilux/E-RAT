#pragma once

#include <map>
#include <functional>
#include <string>
#include "String.hpp"

#include <thread>
#include <memory>

#include "SocketServer.hpp"

namespace ERat
{
	class	Shell {
		using callback_function = std::function<bool (std::list<cpp::String> const&)>;
	public:
		Shell();
		~Shell();

		bool	initialize();
		void	run();

	private:
		bool	executeCommand(std::list<cpp::String> const& args);
		bool	listClients(std::list<cpp::String> const& args);
		bool	useClient(std::list<cpp::String> const& args);

	private:
		std::map<std::string, callback_function>	_map;
		SocketServer 								_server;
		std::unique_ptr<std::thread>				_serverThread;
		std::shared_ptr<SocketClient>				_usedClient;
	};
}