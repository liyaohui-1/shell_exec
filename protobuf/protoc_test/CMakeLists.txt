cmake_minimum_required(VERSION 3.16)

project(test_protobuf)

add_compile_options(-w)

list(APPEND CMAKE_PREFIX_PATH "/home/lyh/shell_exec/protobuf/out/protobuf_install/${PLANT_FORAMT}")


find_package(Protobuf REQUIRED)
if ( Protobuf_FOUND )
    message( STATUS "Protobuf version : ${Protobuf_VERSION}" )
    message( STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}" )
    message( STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}" )
else()
    message( WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)

aux_source_directory(. SRC_FILES)
set(PROCOBUF_DATA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/data/test_data.pb.cc)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${PROCOBUF_DATA_SRC})

target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARIES})