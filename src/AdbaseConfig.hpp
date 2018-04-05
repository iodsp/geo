#ifndef GEO_ADBASE_CONFIG_HPP_
#define GEO_ADBASE_CONFIG_HPP_

#include <string>
#include <adbase/Net.hpp>
#include <adbase/Metrics.hpp>

// {{{ macros

#ifndef DECLARE_KAFKA_CONSUMER_CONFIG
#define DECLARE_KAFKA_CONSUMER_CONFIG(name) \
	std::string topicNameConsumer##name;\
	std::string groupId##name;\
	std::string brokerListConsumer##name;\
	std::string kafkaDebug##name;\
	std::string offsetPath##name;\
	std::string statInterval##name;\
	bool isNewConsumer##name;
#endif
#ifndef DECLARE_KAFKA_PRODUCER_CONFIG
#define DECLARE_KAFKA_PRODUCER_CONFIG(name) \
	std::string topicNameProducer##name;\
	std::string brokerListProducer##name;\
	std::string debug##name;\
	int queueLength##name;
#endif
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
	bool isStartHead;	
	bool isStartHttp;	

	std::string httpHost;
	int httpPort;
	int httpTimeout;
	int httpThreadNum;
	std::string httpDefaultController;
	std::string httpDefaultAction;
	std::string httpServerName;
	std::string httpAccessLogDir;
	int httpAccesslogRollSize;

	std::string headHost;
	int headPort;
	std::string headServerName;
	int headThreadNum;

	std::string mcHost;
	int mcPort;
	std::string mcServerName;
	int mcThreadNum;
	DECLARE_TIMER_CONFIG(Default);
} AdbaseConfig;

class App;
typedef struct adserverContext {
	AdbaseConfig* config;
	adbase::EventBasePtr mainEventBase;	
	App* app;
	adbase::metrics::Metrics* metrics;
	// 前后端交互数据指针添加到下面
} AdServerContext;

typedef struct timerContext {
	AdbaseConfig* config;
	adbase::EventBasePtr mainEventBase;	
	App* app;
	// 定时器交互上下文
} TimerContext;

#endif