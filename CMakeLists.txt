cmake_minimum_required(VERSION 3.15)
project(lesson_sim_1)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE
        ${ROOT_PATH}/remoteApi/extApi.c
        ${ROOT_PATH}/remoteAPi/extApiPlatform.c
        )

include_directories(${ROOT_PATH}/remoteApi ${ROOT_PATH}/include ${ROOT_PATH}/simMath)

add_definitions(-DNON_MATLAB_PARSING)
add_definitions(-DMAX_EXT_API_CONNECTIONS=255)
add_definitions(-DDO_NOT_USE_SHARED_MEMORY)

add_executable(lesson_sim_1 main.cpp ${SOURCE})