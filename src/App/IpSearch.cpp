#include <adbase/Logging.hpp>
#include "IpSearch.hpp"
#include "IpUtils.hpp"
#include <fstream>

namespace app {
// {{{ IpSearch::init()

bool IpSearch::init(const std::string& locationFile) {
	loadLocationFile(locationFile);
	return false;
}

// }}}
// {{{ IpSearch::search()

bool IpSearch::search(const std::string& ip, LocationCodeInfo& info) {
	std::lock_guard<std::mutex> lk(_mut);
	if (!IpUtils::valid(ip)) {
		LOG_INFO << "Search ip address is invalid, ip:" << ip;
		return false;
	}


	uint32_t searchIp = IpUtils::ip2long(ip);
	uint32_t ipZoneLength = _ipZones.size();
	if (ipZoneLength == 0) {
		return false;
	}

	int startIndex = 0;
	int endIndex = ipZoneLength - 1;

	std::string code = "0";
	while(endIndex - startIndex > 0) {
	    uint32_t middleIndex = static_cast<uint32_t>((startIndex + endIndex) / 2);
		if(_ipZones[middleIndex].start == searchIp) {
			code = 	_ipZones[middleIndex].code;
			break;
		} else if(_ipZones[middleIndex].start > searchIp){
			endIndex = middleIndex - 1;
		} else {
			startIndex = middleIndex + 1;
		}
	}

	if(startIndex > 0 && _ipZones[startIndex - 1].end >= searchIp && _ipZones[startIndex - 1].start <= searchIp) {
		code = _ipZones[startIndex - 1].code;
	}
	if(_ipZones[startIndex].end >= searchIp && _ipZones[startIndex].start <= searchIp) {
		code = _ipZones[startIndex].code;
	}

	if (_codeInfos.find(code) != _codeInfos.end()) {
		info = _codeInfos[code]; 
		return true;
	}

	return false;
}

// }}}
// {{{ IpSearch::loadLocationFile()

bool IpSearch::loadLocationFile(const std::string& locationFile) {
	std::lock_guard<std::mutex> lk(_mut);
	std::ifstream ifs(locationFile.c_str(), std::ios_base::in);
	if (!ifs.good() || !ifs.is_open()) {
		return false;
	}

	std::string lineData;
	while(std::getline(ifs, lineData)) {
		std::vector<std::string> info = adbase::explode(lineData, '\t', true);
		if (info.size() != 3) {
			continue;
		}


		std::string code = info[2];
		IpZone ipZone;
		if (!paserIpZone(info[0], code, ipZone)) {
			continue;	
		}

		_ipZones.push_back(ipZone);
		if (_codeInfos.find(code) != _codeInfos.end()) {
			continue;
		}

		std::vector<std::string> address = adbase::explode(info[1], '-', true);
		if (address.size() != 3) {
			continue;
		}

		LocationCodeInfo codeInfo;
		codeInfo.code = code;
		codeInfo.country = address[0];
		codeInfo.province = address[1];
		codeInfo.city = address[2];
		_codeInfos[code] = codeInfo;
	}

	if (!_ipZones.empty()) {
		std::sort(_ipZones.begin(), _ipZones.end());
		return true;
	}

	return false;
}

// }}}
// {{{ IpSearch::paserIpZone()

bool IpSearch::paserIpZone(const std::string& ip, const std::string& code, IpZone& ipZone) {
	std::vector<std::string> ipRange = adbase::explode(ip, '-', true);
	if (ipRange.size() != 2) {
		LOG_INFO << "Ip range info invalid, ip:" << ip;
		return false;
	}

	if (!IpUtils::valid(ipRange[0]) || !IpUtils::valid(ipRange[1])) {
		LOG_INFO << "Ip range info invalid, ip:" << ip;
		return false;
	}

	ipZone.start = IpUtils::ip2long(ipRange[0]);
	ipZone.end   = IpUtils::ip2long(ipRange[1]);
	ipZone.code  = code;
	return true;
}

// }}}
}
