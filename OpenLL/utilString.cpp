#include "utilString.h"

using namespace util;

std::vector<std::string> util::explode(const std::string source, const char* breaker) {
	std::vector<std::string> ret;
	auto pos = 0;
	while (true) {
		auto found = source.find(breaker, pos + 1);
		if (found != std::string::npos) {
			ret.push_back(source.substr(pos, found - pos));
			pos = found + 1;
		} else {
			auto end = source.substr(pos);
			if (end.size() >= 1)
				ret.push_back(end);
			break;
		}
	}
	return ret;
}

std::string util::GetExtension(std::string filename) {
	return filename.substr(filename.find_last_of(".") + 1);
}