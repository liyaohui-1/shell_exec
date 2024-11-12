cmake_minimum_required(VERSION 3.10)

add_compile_options(-w)

set(ZeroMQ_DIR "${CMAKE_SOURCE_DIR}/../install/lib/cmake/ZeroMQ")
find_package(ZeroMQ REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

message(STATUS "ZeroMQ_INCLUDE_DIR: ${ZeroMQ_INCLUDE_DIR}")
message(STATUS "ZeroMQ_LIBRARY:     ${ZeroMQ_LIBRARY}")

include_directories(${ZeroMQ_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../zmq_guide/zguide/examples/C)

add_executable(server_zmq  cli_srv/server.cpp)
target_link_libraries(server_zmq PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(server_zmq_cpp  cli_srv/server_cpp.cpp)
# target_link_libraries(server_zmq_cpp PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(client_zmq  cli_srv/client.cpp)
# target_link_libraries(client_zmq PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(server_zmq_multithread  cli_srv/multithread_server.cpp)
# target_link_libraries(server_zmq_multithread PRIVATE pthread ${ZeroMQ_LIBRARY})

# add_executable(weather_srv  weather_cli_srv/weather_srv.cpp)
# target_link_libraries(weather_srv PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(weather_cli  weather_cli_srv/weather_cli.cpp)
# target_link_libraries(weather_cli PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(dispatcher  task_calculate/task_dispatcher.cpp)
# target_link_libraries(dispatcher PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(worker  task_calculate/task_worker.cpp)
# target_link_libraries(worker PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(collector  task_calculate/task_collecter.cpp)
# target_link_libraries(collector PRIVATE ${ZeroMQ_LIBRARY})

# add_executable(zmq_multithread_sync  zmq_sync/multithread_sync.cpp)
# target_link_libraries(zmq_multithread_sync PRIVATE pthread ${ZeroMQ_LIBRARY})

add_executable(syncsub  zmq_sync/node_sync_sub.cpp)
target_link_libraries(syncsub PRIVATE pthread ${ZeroMQ_LIBRARY})

add_executable(syncpub  zmq_sync/node_sync_pub.cpp)
target_link_libraries(syncpub PRIVATE pthread ${ZeroMQ_LIBRARY})