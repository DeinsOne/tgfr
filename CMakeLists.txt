cmake_minimum_required(VERSION 3.1)
project(tgfr)

# options
option(BUILD_SHARED_LIBS "Build tgfr shared/static library." OFF)
option(BUILD_SAMPLES "Build tgfr example projects." OFF)

# sources
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib")
endif()

set(TGFR_INCLUDE_DIRS include)

include_directories(${TGFR_INCLUDE_DIRS})
set(TGFR_SRC_LIST 
    src/Bot.cpp
    src/BotAsync.cpp
    src/BotSync.cpp
    src/logger/Logger.cpp
    src/handler/EventHandler.cpp
    src/manager/EventWorker.cpp
)

# libs
## threads
find_package(Threads REQUIRED)

## zlib
find_package(ZLIB REQUIRED)

## openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

## curl
find_package(CURL 7.56.0)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

# spdlog
find_package(spdlog REQUIRED)

set(TGFR_LIB_LIST
    ${CMAKE_THREAD_LIBS_INIT}
    ${ZLIB_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
    TgBot
)


# building project
add_library(${PROJECT_NAME} ${TGFR_SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${TGFR_LIB_LIST})
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# ABI version
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 1)


# samples
if (BUILD_SAMPLES)
    message(STATUS "Building sample projects is enabled")
    set(TGFR_LIB ${PROJECT_NAME})
    add_subdirectory(samples/echo_bot)
    add_subdirectory(samples/event_error_bot)
endif()
