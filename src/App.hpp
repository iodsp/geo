#ifndef GEO_APP_HPP_
#define GEO_APP_HPP_

#include <adbase/Config.hpp>
#include "AdbaseConfig.hpp"
#include "App/IpSearch.hpp"

class App {
public:
	App(AdbaseConfig* config);
	~App();
	void reload();
	void run();
	void stop();
	void setAdServerContext(AdServerContext* context);
	void setTimerContext(TimerContext* context);
	void loadConfig(adbase::IniConfig& config);
	uint64_t getSeqId();

private:
	AdbaseConfig* _configure;
	mutable std::mutex _mut;
	std::shared_ptr<app::IpSearch> _ipSearch;
};

#endif
