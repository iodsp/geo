#ifndef GEO_IPUTILS_HPP_
#define GEO_IPUTILS_HPP_

#include <adbase/Utility.hpp>

namespace app {
class IpUtils {
public:
	static uint32_t ip2long(const std::string& ip);
	static std::string long2ip(uint32_t iplong);
	static bool valid(const std::string& ip);
};
}

#endif
