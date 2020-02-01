#include <map>
#include <functional>
#include <string>

namespace ERat
{
	class	Shell {
		using callback_function = std::function<bool (std::string const&, std::vector<std::string> const&)>;
	public:
		Shell();
		~Shell();

		bool	initialize();
		void	run();

	private:
		std::map<std::string, callback_function>	_map;
	};
}