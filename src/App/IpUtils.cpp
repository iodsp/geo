#include "IpUtils.hpp"
#include <adbase/Logging.hpp>

namespace app {
// {{{ IpUtils::ip2long()

uint32_t IpUtils::ip2long(const std::string& ip) {
	std::vector<std::string> ipItems = adbase::explode(ip, '.', true);
	uint32_t result = 0;
	errno = 0;
	if (ipItems.size() != 4) {
		return result;	
	}

	int i = 3;
	for (auto item : ipItems) {
		uint32_t num = static_cast<uint32_t>(strtoul(item.c_str(), nullptr, 10));
		if (errno != 0) {
			return false;
		}
		result += static_cast<uint32_t>(num * std::pow(256, i));	
		i--;
	}
	return result;
}

// }}}
// {{{ IpUtils::long2ip()

std::string IpUtils::long2ip(uint32_t iplong) {
	uint32_t ip[4];
	ip[0] = (iplong >> 24) >> 0;
	ip[1] = ((iplong << 8) >> 24) >> 0;
	ip[2] = (iplong << 16) >> 24;
	ip[3] = (iplong << 24) >> 24;

	std::string strIP = "";
	for(int i = 0; i < 4;i++) {
		if(ip[i] > 255) {
			return "0.0.0.0";
		}
		strIP += std::to_string(ip[i]) + ".";
	}
	return strIP;
}

// }}}
// {{{ IpUtils::valid()

bool IpUtils::valid(const std::string& ip) {
	errno = 0;
	std::vector<std::string> ipItems = adbase::explode(ip, '.', true);
	if (ipItems.size() != 4) {
		return false;	
	}

	for (auto& item : ipItems) {
		uint32_t num = static_cast<uint32_t>(strtoul(item.c_str(), nullptr, 10));
		(void)num;
		if (errno != 0) {
			return false;
		}
	}
	return true;
}

// }}}
}
