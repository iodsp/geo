#include <adbase/Utility.hpp>
#include <adbase/Logging.hpp>
#include "App.hpp"
#include "App/IpUtils.hpp"

//{{{ macros

#define LOAD_TIMER_CONFIG(name) do {\
	_configure->interval##name = config.getOptionUint32("timer", "interval"#name);\
} while(0)

//}}}
// {{{ App::App()

App::App(AdbaseConfig* config) :
	_configure(config) {
}

// }}}
// {{{ App::~App()

App::~App() {
}

// }}}
// {{{ void App::run()

void App::run() {
	_ipSearch = std::shared_ptr<app::IpSearch>(new app::IpSearch());
	_ipSearch->init(_configure->locationPath);
}

// }}}
// {{{ void App::reload()

void App::reload() {
}

// }}}
// {{{ void App::stop()

void App::stop() {
}

// }}}
// {{{ void App::setAdServerContext()

void App::setAdServerContext(AdServerContext* context) {
	context->app = this;
	context->ipSearch = _ipSearch.get();
}

// }}}
// {{{ void App::setTimerContext()

void App::setTimerContext(TimerContext* context) {
	context->app = this;
}

// }}}
//{{{ void App::loadConfig()

void App::loadConfig(adbase::IniConfig& config) {
	
	LOAD_TIMER_CONFIG(DefaultTimer);
    _configure->locationPath = config.getOption("ipsearch", "locationPath");\
}

//}}}
//{{{ uint64_t App::getSeqId()

uint64_t App::getSeqId() {
	std::lock_guard<std::mutex> lk(_mut);
	adbase::Sequence seq;
	return seq.getSeqId(static_cast<uint16_t>(_configure->macid), static_cast<uint16_t>(_configure->appid));
}

//}}}
