#pragma once
cmake_minimum_required(VERSION 3.20)

project (server-cmake)
set(_CMAKE_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(server-cmake Server.cpp)




target_link_libraries(server-cmake PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

