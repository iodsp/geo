#ifndef GEO_GRPC_SERVER_SERVICE_IMPL_HPP_
#define GEO_GRPC_SERVER_SERVICE_IMPL_HPP_
#include <grpc++/grpc++.h>
#include "adbase.grpc.pb.h"
#include "AdbaseConfig.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using geo::StatusRequest;
using geo::StatusReply;

namespace adserver {
namespace grpc {
class ServerServiceImpl final : public geo::Server::Service {
public:
	ServerServiceImpl(AdServerContext* context);
	Status status(ServerContext* context, const StatusRequest* request, StatusReply* reply) override;
private:
	AdServerContext* _context;
	AdbaseConfig* _configure;
};
}
}
#endif