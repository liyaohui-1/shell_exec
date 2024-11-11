#!/bin/bash

CURR_DIR=$(pwd)
ZMQ_SRC_DIR=$CURR_DIR/libzmq
ZMQ_BUILD_DIR=$CURR_DIR/build
ZMQ_INDSTALL_DIR=$CURR_DIR/install

if [ ! -d ${ZMQ_SRC_DIR} ]; then
    echo "zmq source dir not exist"
    exit 0
fi

if [ ! -d ${ZMQ_BUILD_DIR} ]; then
    mkdir -p ${ZMQ_BUILD_DIR}
fi

if [ ! -d ${ZMQ_INDSTALL_DIR} ]; then
    mkdir -p ${ZMQ_INDSTALL_DIR}
fi

for i in "$@"; do
    case $i in
    clean)
        echo "clean thirdparty libzmq..."
        rm -rf ${ZMQ_BUILD_DIR}
        rm -rf ${ZMQ_INDSTALL_DIR}
        break
        ;;
    build)
        echo "build thirdparty libzmq ..."
        pushd $ZMQ_BUILD_DIR
        cmake  -DZMQ_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$ZMQ_INDSTALL_DIR $ZMQ_SRC_DIR || exit 1
        cmake --build . --parallel || exit 1
        cmake --build . --target install
        popd
        break
        ;;
    *)
        echo "usage"
        echo "build build  libzmq"
        echo "clean clean  libzmq"
        ;;
    esac
done