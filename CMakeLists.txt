cmake_minimum_required(VERSION 3.10)
project(PubSub)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(examples)

add_library(pubsub_lib
    src/Broker.cpp
    src/Publisher.cpp
    src/Subscriber.cpp
)

add_executable(main_publisher examples/main_publisher.cpp)
add_executable(main_subscriber examples/main_subscriber.cpp)

target_link_libraries(pubsub_lib pthread rt)  # Link with pthread and rt libraries
target_link_libraries(main_publisher pubsub_lib pthread)
target_link_libraries(main_subscriber pubsub_lib pthread)
