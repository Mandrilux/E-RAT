
#include "String.hpp"

namespace cpp
{
    /*
     * Default constructor for String
     * Nothing to do
     */
    String::String() = default;

    /*
     * Constructor with const char*
     */
    String::String(const char *str) : std::string(str) {

    }

    /*
     * Constructor with const std::string&
     */
    String::String(const std::string &str) : std::string(str) {

    }

    /**
     * Assignment operator
     * @param str: const char* to be transform into String
     * @return String&
     */
    String& String::operator=(const char *str) {
        return (String&)(this->assign(str));
    }

    /**
     * Assignment operator
     * @param str: const char* to be transform into String
     * @return String&
     */
    String& String::operator=(const std::string& str) {
        return (String&)(this->assign(str));
    }

    /**
     * Tokenization function
     * This function split the current string into a list of String
     * Depending on which separators are passed as paramaters
     * @param separators: if empty, split char by char
     * @return
     */
    std::list<String>   String::tokenize(const cpp::String &separators) const {
        std::list<String>   result;
        String::const_iterator  iterator = this->begin();

        while (separators.find(*iterator) != std::string::npos) {
            ++iterator;
        }
        while (iterator != this->end()) {
            auto token = std::string();

            do {
                token += *iterator;
                ++iterator;
            } while (iterator != this->end() &&
                     separators.find(*iterator) == std::string::npos &&
                     separators.size() > 0);

            if (token.size()) {
                result.push_back(token);
            }
            while (iterator != this->end() &&
                   separators.find(*iterator) != std::string::npos &&
                    separators.size() > 0) {
                ++iterator;
            }
        }
        return result;
    }

    /*
     * Default destructor for String
     * Nothing to do
     */
    String::~String() = default;
}