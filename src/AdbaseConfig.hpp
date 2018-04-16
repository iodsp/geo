#ifndef GEO_ADBASE_CONFIG_HPP_
#define GEO_ADBASE_CONFIG_HPP_

#include <string>
#include <adbase/Net.hpp>
#include <adbase/Metrics.hpp>

// {{{ macros

#ifndef DECLARE_TIMER_CONFIG
#define DECLARE_TIMER_CONFIG(name) \
	int interval##name;
#endif

// }}}

typedef struct adbaseConfig {
	bool daemon;
	std::string pidFile;
	int appid;
	int macid;
	
	// logging config
	std::string logsDir;
	size_t logRollSize;
	int logLevel;
	bool isAsync;
	
	bool isStartMc;	
	bool isStartHttp;	
	bool isStartGrpc;

	std::string httpHost;
	int httpPort;
	int httpTimeout;
	int httpThreadNum;
	std::string httpDefaultController;
	std::string httpDefaultAction;
	std::string httpServerName;
	std::string httpAccessLogDir;
	int httpAccesslogRollSize;

	std::string grpcHost;
	int grpcPort;

	std::string mcHost;
	int mcPort;
	std::string mcServerName;
	int mcThreadNum;
	DECLARE_TIMER_CONFIG(DefaultTimer);

	std::string locationPath;
} AdbaseConfig;

class App;
namespace app {
class IpSearch;
}
typedef struct adserverContext {
	AdbaseConfig* config;
	adbase::EventBasePtr mainEventBase;	
	App* app;
	adbase::metrics::Metrics* metrics;
	// 前后端交互数据指针添加到下面
	app::IpSearch* ipSearch;
} AdServerContext;

typedef struct timerContext {
	AdbaseConfig* config;
	adbase::EventBasePtr mainEventBase;	
	App* app;
	// 定时器交互上下文
} TimerContext;

#endif
