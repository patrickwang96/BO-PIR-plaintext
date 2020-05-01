cmake_minimum_required(VERSION 3.10)
project(BO_PIR)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include )
find_package(Boost 1.40.0 REQUIRED system)

link_directories(/usr/local/lib/ /usr/local/opt/openssl/lib/)
add_executable(client boost_client.cpp)
add_executable(pir main.cpp pir.cpp pir.h)
add_executable(source source_main.cpp pir.cpp pir.h)
target_link_libraries(source crypto ssl )
