#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

#include "envoy/common/pure.h"

#include "envoy/config/core/v3/grpc_service.pb.h"
#include "envoy/grpc/async_client.h"
#include "envoy/grpc/async_client_manager.h"


#include "envoy/service/tls_session_cache/v3/tls_session_cache.pb.h"
// #include "envoy/stats/scope.h"

#include "source/common/common/logger.h"
#include "source/common/grpc/typed_async_client.h"
#include "source/common/singleton/const_singleton.h"

namespace Envoy {
namespace Extensions {
namespace TransportSockets {
namespace Tls {
namespace SessionCache {


class RequestCallbacks {
public:
  virtual ~RequestCallbacks() = default;

  virtual void completeStore(const std::string& session_id) PURE;
  virtual void completeFetch(const std::string& session_id) PURE;
};


class Client {
public:
  virtual ~Client() = default;


  /**
   * Request to store a TLS session to remote cache.
   * NOTE: It is possible for the completion callback to be called immediately on the same stack
   *       frame. Calling code should account for this.
   * @param callbacks supplies the completion callbacks.
   * @param session_id supplies the session id
   * @param parent_span source for generating an egress child span as part of the trace.
   * @param stream_info supplies the stream info for the request.
   *
   */
  virtual void store(RequestCallbacks& callbacks, const std::string& session_id,
                     Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) PURE;

  /**
   * Request to fetch a TLS session from remote cache.
   * NOTE: It is possible for the completion callback to be called immediately on the same stack
   *       frame. Calling code should account for this.
   * @param callbacks supplies the completion callbacks.
   * @param session_id supplies the session id
   * @param parent_span source for generating an egress child span as part of the trace.
   * @param stream_info supplies the stream info for the request.
   *
   */
  virtual void fetch(RequestCallbacks& callbacks, const std::string& session_id,
                     Tracing::Span& parent_span, const StreamInfo::StreamInfo& stream_info) PURE;

};

using ClientPtr = std::unique_ptr<Client>;

} // namespace SessionCache
} // namespace Tls
} // namespace TransportSockets
} // namespace Extensions
} // namespace Envoy
