#include <grpc++/grpc++.h>
#include "ipsearch.grpc.pb.h"
#include "AdbaseConfig.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using appproto::IpSearchRequest;
using appproto::IpSearchReply;
using appproto::IpSearch;

namespace adserver {
namespace grpc {
class IpSearchServiceImpl final : public IpSearch::Service {
public:
	IpSearchServiceImpl(AdServerContext* context);
	Status search(ServerContext* context, const IpSearchRequest* request, IpSearchReply* reply) override;
private:
	AdServerContext* _context;
	AdbaseConfig* _configure;
};
}
}

