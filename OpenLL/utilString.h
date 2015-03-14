#ifndef __UTIL_STRING_H__
#define __UTIL_STRING_H__

#include <string>
#include <sstream>
#include <vector>

namespace util {
	template <class T> 
	std::string toString(const T& input) {
		std::stringstream stream;
		stream << input;
		return stream.str();
	}

	template <class T> 
	T stringTo(const std::string& parseString, std::ios_base& (*f)(std::ios_base&) = std::dec) {
		T temp;
		std::istringstream iss(parseString);
		return !(iss >> f >> temp).fail() ? temp : temp;
	}

	std::vector<std::string> explode(const std::string source, const char* breaker);

	std::string GetExtension(std::string filename);
}

#endif