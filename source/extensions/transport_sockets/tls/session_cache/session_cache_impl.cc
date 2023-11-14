#include "source/extensions/transport_sockets/tls/session_cache/session_cache_impl.h"

namespace Envoy {
namespace Extensions {
namespace TransportSockets {
namespace Tls {
namespace SessionCache {


GrpcClientImpl::GrpcClientImpl(const Grpc::RawAsyncClientSharedPtr& async_client,
                               const absl::optional<std::chrono::milliseconds>& timeout)
    : async_client_(async_client), timeout_(timeout),
      service_method_(*Protobuf::DescriptorPool::generated_pool()->FindMethodByName(
          "envoy.service.tls_session_cache.v3.TlsSessionCacheService.StoreTlsSession")) {}

GrpcClientImpl::~GrpcClientImpl() { ASSERT(!callbacks_); }



void GrpcClientImpl::store(RequestCallbacks& callbacks, const std::string& session_id,
                    Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) {

}
void GrpcClientImpl::fetch(RequestCallbacks& callbacks, const std::string& session_id,
                    Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) {

}

// Grpc::AsyncRequestCallbacks
void GrpcClientImpl::onSuccess(std::unique_ptr<envoy::service::tls_session_cache::v3::StoreTlsSessionResponse>&& response,
                Tracing::Span& span) {

}
void GrpcClientImpl::onFailure(Grpc::Status::GrpcStatus status, const std::string& message,
                Tracing::Span& span) {

}




} // namespace SessionCache
} // namespace Tls
} // namespace TransportSockets
} // namespace Extensions
} // namespace Envoy
