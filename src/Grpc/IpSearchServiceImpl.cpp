#include <grpc++/grpc++.h>
#include "ipsearch.grpc.pb.h"
#include "IpSearchServiceImpl.hpp"
#include "App/IpSearch.hpp"

namespace adserver {
namespace grpc {
// {{{ IpSearchServiceImpl::IpSearchServiceImpl()

IpSearchServiceImpl::IpSearchServiceImpl(AdServerContext* context) : _context(context) {
	_configure = _context->config;
}

// }}}
// {{{ IpSearchServiceImpl::search()

Status IpSearchServiceImpl::search(ServerContext* context, const IpSearchRequest* request, IpSearchReply* reply) {
	if (_context->ipSearch == nullptr) {
		Status status(::grpc::UNIMPLEMENTED, "Not start");
		return status;
	}

	app::LocationCodeInfo info;
	_context->ipSearch->search(request->ip(), info);
	reply->set_code(info.code);
	reply->set_country(info.country);
	reply->set_province(info.province);
	reply->set_city(info.city);
	return Status::OK;
}

// }}}
}
}
