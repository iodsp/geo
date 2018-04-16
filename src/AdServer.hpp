/// 该程序自动生成，禁止修改
#ifndef GEO_ADSERVER_HPP_
#define GEO_ADSERVER_HPP_

#include <adbase/Utility.hpp>
#include <adbase/Logging.hpp>
#include <adbase/Http.hpp>
#include <adbase/Net.hpp>
#include <adbase/Mc.hpp>
#include "AdbaseConfig.hpp"
#include "Http.hpp"
#include "McProcessor.hpp"
#include "Grpc.hpp"

class AdServer {
public:
	AdServer(AdServerContext* context);
	~AdServer();
	void run();
	std::string httpFallback(const std::string& url);

private:
	AdbaseConfig* _configure;
	/// 传输上下文指针
	AdServerContext* _context; 
	adbase::EventBasePtr _base;

	/// http server
	std::shared_ptr<adbase::http::Server> _http;
	std::shared_ptr<Http> _httpManager;
	/// mc server
	std::shared_ptr<McProcessor> _mcProcessor;
	std::shared_ptr<adbase::TcpServer> _mcServer;
	std::shared_ptr<adbase::InetAddress> _mcAddr;
	std::shared_ptr<adbase::mc::Interface> _mcInterface;
	std::shared_ptr<adbase::mc::Handler> _mcHandler;
	std::shared_ptr<Grpc> _grpcServer;

	void init();
	void stop();
	void initHttp();
	void initGrpc();
	void initMc();
	void bindMcCallback();
};

#endif