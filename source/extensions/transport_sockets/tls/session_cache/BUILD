load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

envoy_extension_package()

envoy_cc_library(
    name = "tls_session_cache_lib",
    srcs = [
        "session_cache_impl.cc",
    ],
    hdrs = [
        "session_cache_impl.h",
    ],
    copts = [
        "-Wno-comments",
        "-Wno-unused-parameter",
    ],
    deps = [
        ":tls_session_cache_client_interface",
        "//envoy/event:dispatcher_interface",
        "//envoy/grpc:async_client_interface",
        "//envoy/grpc:async_client_manager_interface",
        "//source/common/common:assert_lib",
        "//source/common/grpc:typed_async_client_lib",
        "//envoy/registry",
        "@envoy_api//envoy/extensions/transport_sockets/tls/v3:pkg_cc_proto",
        "@envoy_api//envoy/service/tls_session_cache/v3:pkg_cc_proto",
    ],
)

envoy_cc_library(
    name = "tls_session_cache_client_interface",
    hdrs = ["session_cache.h"],
    external_deps = ["abseil_optional"],
    deps = [
        "//envoy/common:pure_lib",
        "@envoy_api//envoy/service/ratelimit/v3:pkg_cc_proto",
    ],
)
