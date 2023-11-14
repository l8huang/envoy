#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

#include "envoy/config/core/v3/grpc_service.pb.h"
#include "envoy/grpc/async_client.h"
#include "envoy/grpc/async_client_manager.h"
#include "source/extensions/transport_sockets/tls/session_cache/session_cache.h"


#include "envoy/service/tls_session_cache/v3/tls_session_cache.pb.h"
#include "envoy/stats/scope.h"
#include "envoy/server/factory_context.h"

#include "source/common/common/logger.h"
#include "source/common/grpc/typed_async_client.h"
#include "source/common/singleton/const_singleton.h"

namespace Envoy {
namespace Extensions {
namespace TransportSockets {
namespace Tls {
namespace SessionCache { 

using StoreTlsSessionAsyncCallbacks =
    Grpc::AsyncRequestCallbacks<envoy::service::tls_session_cache::v3::StoreTlsSessionResponse>;

using FetchTlsSessionAsyncCallbacks =
    Grpc::AsyncRequestCallbacks<envoy::service::tls_session_cache::v3::FetchTlsSessionResponse>;

class GrpcClientImpl : public Client,
                       public StoreTlsSessionAsyncCallbacks,
                       public Logger::Loggable<Logger::Id::config> {
public:
  GrpcClientImpl(const Grpc::RawAsyncClientSharedPtr& async_client,
                 const absl::optional<std::chrono::milliseconds>& timeout);
  ~GrpcClientImpl() override;

  // Client
  virtual void store(RequestCallbacks& callbacks, const std::string& session_id,
                     Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) override;
  virtual void fetch(RequestCallbacks& callbacks, const std::string& session_id,
                     Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) override;

  // Grpc::AsyncRequestCallbacks
  void onCreateInitialMetadata(Http::RequestHeaderMap&) override {}
  void onSuccess(std::unique_ptr<envoy::service::tls_session_cache::v3::StoreTlsSessionResponse>&& response,
                 Tracing::Span& span) override;
  void onFailure(Grpc::Status::GrpcStatus status, const std::string& message,
                 Tracing::Span& span) override;

private:
  Grpc::AsyncClient<envoy::service::tls_session_cache::v3::StoreTlsSessionRequest,
                    envoy::service::tls_session_cache::v3::StoreTlsSessionResponse>
      async_client_;
//   Grpc::AsyncRequest* request_{};
  absl::optional<std::chrono::milliseconds> timeout_;
  RequestCallbacks* callbacks_{};
  const Protobuf::MethodDescriptor& service_method_;
};

/**
 * Builds the tls session cache client.
 */
ClientPtr tlsSessionCacheClient(Server::Configuration::FactoryContext& context,
                          const Grpc::GrpcServiceConfigWithHashKey& config_with_hash_key,
                          const std::chrono::milliseconds timeout);

} // namespace SessionCache
} // namespace Tls
} // namespace TransportSockets
} // namespace Extensions
} // namespace Envoy
