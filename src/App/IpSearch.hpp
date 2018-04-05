#ifndef GEO_IPSEARCH_HPP_
#define GEO_IPSEARCH_HPP_
#include <adbase/Utility.hpp>

namespace app {

typedef struct {
	std::string code;
	std::string country;
	std::string province;
	std::string city;
} LocationCodeInfo;

typedef struct ipZone {
	uint32_t start;
	uint32_t end;
	std::string code;

	bool operator<(const ipZone other) const {
		return start < other.start;
	}
} IpZone;

class IpSearch {
public:
	bool init(const std::string& locationFile);
	bool search(const std::string& ip, LocationCodeInfo& info);
private:
	bool loadLocationFile(const std::string& locationFile);
	bool paserIpZone(const std::string& ipRange, const std::string& code, IpZone& ipZone);
	std::unordered_map<std::string, LocationCodeInfo> _codeInfos;
	std::vector<IpZone> _ipZones;
	mutable std::mutex _mut;
};
}

#endif
