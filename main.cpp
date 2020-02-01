#include "src/Shell.hpp"
#include "src/SocketServer.hpp"

int	main()
{
	ERat::Shell	shell;
	SocketServer *server;
	server = new SocketServer(8080);
	server->run();
	if (shell.initialize()) {
		shell.run();
		return 0;
	}
	server->close();
	return EXIT_SUCESS;
}
