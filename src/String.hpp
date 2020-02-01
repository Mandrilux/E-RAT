//
// Created by Arnaud WURMEL on 28/2/19.
//

#ifndef CPPHELPER_STRING_HH
#define CPPHELPER_STRING_HH

#include <string>
#include <list>

namespace cpp {
    class String: public std::string {
        /*
         * Constructor & Destructor
         */
    public:
        String();
        String(const char *str);
        String(const std::string& str);
        virtual ~String();

    public:
        std::list<String>   tokenize(const String& separators = "") const;

        /*
         * Operators
         */
    public:
        String& operator=(const std::string& str);
        String& operator=(const char* str);
    };
}


#endif //CPPHELPER_STRING_HH