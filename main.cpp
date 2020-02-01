#include "src/Shell.hpp"
#include "src/SocketServer.hpp"

int	main()
{
	ERat::Shell	shell;
	if (shell.initialize()) {
		shell.run();
		return 0;
	}
	return EXIT_SUCESS;
}
