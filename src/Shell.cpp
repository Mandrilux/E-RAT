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
		return true;
	}

	void	Shell::run()
	{
		cpp::String	line;

		std::cout << "> ";
		while (std::getline(std::cin, line))
		{
			std::cout << "Read: " << line.tokenize(" \t").front() << std::endl;
			std::cout << "> ";
		}
	}

	Shell::~Shell() = default;
}

