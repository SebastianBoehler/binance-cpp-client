cmake_minimum_required(VERSION 3.16)
project(BinanceCppClient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)

file(GLOB_RECURSE BINANCE_STYLE_FILES CONFIGURE_DEPENDS include/*.hpp src/*.cpp tests/*.cpp examples/*.cpp)
file(GLOB_RECURSE BINANCE_LINT_FILES CONFIGURE_DEPENDS src/*.cpp tests/*.cpp examples/*.cpp)

find_program(CLANG_FORMAT_EXE NAMES clang-format HINTS /opt/homebrew/opt/llvm/bin)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${BINANCE_STYLE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror ${BINANCE_STYLE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

find_program(CLANG_TIDY_EXE NAMES clang-tidy HINTS /opt/homebrew/opt/llvm/bin)
if(CLANG_TIDY_EXE)
    set(BINANCE_CLANG_TIDY_ARGS --quiet -p ${CMAKE_BINARY_DIR})
    if(APPLE)
        execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE BINANCE_APPLE_SYSROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)
        if(BINANCE_APPLE_SYSROOT)
            list(APPEND BINANCE_CLANG_TIDY_ARGS --extra-arg=-isysroot --extra-arg=${BINANCE_APPLE_SYSROOT})
        endif()
        list(APPEND BINANCE_CLANG_TIDY_ARGS --extra-arg=-stdlib=libc++)
    endif()
    add_custom_target(lint
        COMMAND ${CLANG_TIDY_EXE} ${BINANCE_CLANG_TIDY_ARGS} ${BINANCE_LINT_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_library(binance_client
    src/futures_account.cpp
    src/futures_client.cpp
    src/futures_market.cpp
    src/futures_trading.cpp
    src/http_client.cpp
    src/http_error.cpp
    src/options_account.cpp
    src/options_client.cpp
    src/options_market.cpp
    src/options_trading.cpp
    src/query.cpp
    src/rest_account.cpp
    src/rest_client.cpp
    src/rest_market.cpp
    src/rest_trading.cpp
    src/signing.cpp
    src/websocket_client.cpp)

target_include_directories(binance_client
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(binance_client PUBLIC OpenSSL::Crypto CURL::libcurl)

option(BINANCE_ENABLE_WEBSOCKET "Enable websocket client implementation with ixwebsocket" OFF)
if(BINANCE_ENABLE_WEBSOCKET)
    include(FetchContent)
    set(USE_TLS ON CACHE BOOL "Enable TLS in ixwebsocket" FORCE)
    set(USE_OPEN_SSL ON CACHE BOOL "Use OpenSSL backend in ixwebsocket" FORCE)
    FetchContent_Declare(
        ixwebsocket
        GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
        GIT_TAG v11.3.3)
    FetchContent_MakeAvailable(ixwebsocket)
    find_package(Threads REQUIRED)
    target_link_libraries(binance_client PUBLIC ixwebsocket::ixwebsocket Threads::Threads)
    target_compile_definitions(binance_client PUBLIC BINANCE_ENABLE_WEBSOCKET=1)
endif()

add_executable(market_snapshot examples/market_snapshot.cpp)
target_link_libraries(market_snapshot PRIVATE binance_client)
add_executable(futures_market_snapshot examples/futures_market_snapshot.cpp)
target_link_libraries(futures_market_snapshot PRIVATE binance_client)
add_executable(options_market_snapshot examples/options_market_snapshot.cpp)
target_link_libraries(options_market_snapshot PRIVATE binance_client)
add_executable(place_test_order examples/place_test_order.cpp)
target_link_libraries(place_test_order PRIVATE binance_client)
add_executable(ws_stream_url examples/ws_stream_url.cpp)
target_link_libraries(ws_stream_url PRIVATE binance_client)

include(GNUInstallDirs)
install(TARGETS binance_client
    EXPORT BinanceCppClientTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT BinanceCppClientTargets
    FILE BinanceCppClientTargets.cmake
    NAMESPACE Binance::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BinanceCppClient)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/BinanceCppClientConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)
configure_file(cmake/BinanceCppClientConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/BinanceCppClientConfig.cmake @ONLY)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/BinanceCppClientConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/BinanceCppClientConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BinanceCppClient)

option(BINANCE_BUILD_TESTS "Build tests" ON)
if(BINANCE_BUILD_TESTS)
    include(CTest)
    foreach(test_name IN ITEMS signing query order_request rest_surface derivatives_surface websocket_topics)
        add_executable(test_${test_name} tests/test_${test_name}.cpp)
        target_link_libraries(test_${test_name} PRIVATE binance_client)
        add_test(NAME ${test_name} COMMAND test_${test_name})
    endforeach()
endif()
