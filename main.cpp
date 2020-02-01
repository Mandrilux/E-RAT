#include "src/Shell.hpp"

int	main()
{
	ERat::Shell	shell;

	if (shell.initialize()) {
		shell.run();
		return 0;
	}
	return 1;
}