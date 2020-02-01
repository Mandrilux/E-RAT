#include <map>
#include <functional>
#include <string>
#include "String.hpp"

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

	private:
		std::map<std::string, callback_function>	_map;
	};
}