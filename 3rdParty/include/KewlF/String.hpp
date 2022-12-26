#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
//#include <format>

using std::cerr;
using std::cout;
using std::endl;

using std::size_t;

//the following produce a strange error in VS Code editor
//using StringStream = std::stringstream;
//typedef std::stringstream StringStream;

typedef std::string String;
typedef std::vector<String> ArrayOfStrings;
typedef std::shared_ptr<String> SharedStringPointer;

template<typename T>
inline String toString(T n) { return std::to_string(n); }

inline SharedStringPointer makeSharedString() { return std::make_shared<String>(); }

inline ArrayOfStrings toArrayOfStrings(const String &str, const char delim) {
    ArrayOfStrings newArrayOfStrings;

    size_t found = str.find_first_of(delim);
    size_t startPos = 0;
    size_t i = 0;
    while (found != String::npos) {
        newArrayOfStrings.push_back(str.substr(startPos, found - startPos));
        cout << "newArrayOfStrings[" << i << "]: " << newArrayOfStrings[i] << endl;
        startPos = found + 1;
        found = str.find_first_of(delim, startPos);
        i++;
    }

    return newArrayOfStrings;
}

inline String eraseAllMatching(const String &str, const String &remStr) {
    String newString = str;
    size_t found = newString.find_first_of(remStr);
    while (found != String::npos) {
        newString.erase(found, 1);
        found = newString.find_first_of(remStr);
    }

    return newString;
}
inline String &trimString(String &str) {
    const String typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    return str;
}

// Emulates format not in GCC/G++, yet to be implimented for c++20 standard
// Taken from https://codereview.stackexchange.com/questions/187183/create-a-c-string-using-printf-style-formatting
// base case of recursion, no more arguments
// not it is also limited, handles %d and everything else as a string i.e. %s
inline void format_impl(std::stringstream& ss, const char* format) {
    while (*format) {
        if (*format == '%' && *++format != '%') // %% == % (not a format directive)
            throw std::invalid_argument("not enough arguments !\n");
        ss << *format++;
    }
}

template <typename Arg, typename... Args>
void format_impl(std::stringstream& ss, const char* format, Arg arg, Args... args) {
    while (*format) {
        if (*format == '%' && *++format != '%') {
            auto current_format_qualifier = *format;
            switch(current_format_qualifier) {
                case 'd':
                    if (!std::is_integral<Arg>()) throw std::invalid_argument("%d introduces integral argument");
                    break;
                // case 'u':
                //     if (!std::is_integer<Arg>()) throw std::invalid_argument("%u introduces integer argument");
                //     break;
                case 'p':
                //     if (!std::is_integer<Arg>()) throw std::invalid_argument("%p introduces integer argument");
                    ss << std::hex << "0x";
                    break;
                // etc.
                default : break;
            }
            // it's true you'd have to handle many more format qualifiers, but on a safer basis
            ss << arg; // arg type is deduced
            return format_impl(ss, ++format, args...); // one arg less
        }
        ss << *format++;
        } // the format string is exhausted and we still have args : throw
    throw std::invalid_argument("Too many arguments\n");
}

template <typename... Args>
std::string format(const char* fmt, Args... args) {
    std::stringstream ss;
    format_impl(ss, fmt, args...);
    return ss.str();
}