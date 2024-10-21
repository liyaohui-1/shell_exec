#!/bin/bash

CURR_DIR=$(pwd)
PROTOBUF_3_5=$CURR_DIR/protobuf-3.5.0
PROTOBUF_3_21_12=$CURR_DIR/protobuf-3.21.12

platform_type="x86"

for i in "$@"; do
    case $i in
    x86)
		platform_type="x86"
		shift
		;;
    tda4)
		platform_type="tda4"
		echo "source /opt/tda4-toolchain/environment-setup..."
        [ -f /opt/tda4-toolchain/environment-setup ] && source /opt/tda4-toolchain/environment-setup
		shift
		;;
    j3)
		platform_type="j3"
		echo "source /opt/j3-toolchain/environment-setup..."
		[ -f /opt/j3-toolchain/environment-setup ] && source /opt/j3-toolchain/environment-setup
		shift
		;;
	3.5)
		protobuf_version="3.5.0"
		shift
		;;
	3.21.12)
		protobuf_version=3.21.12
		shift
		;;
	clean)
		clean_build="yes"
		shift
		;;
    *)
		echo "Usage: enter format as [platform_type][protobuf_version]"
		echo "       clean if you want to clean build"
		exit 1
		;;
    esac
done

OUT_DIR=$CURR_DIR/out
protobuf_install_dir=$OUT_DIR/protobuf_install/$platform_type
protobuf_build_dir=$OUT_DIR/protobuf_build/$platform_type
protobuf_test_dir=/home/lyh/protobuf/protoc_test/build
protobuf_test_types_dir=/home/lyh/protobuf/types/build

if [ ! -d "$protobuf_install_dir" ]; then
	mkdir -p $protobuf_install_dir
fi

if [ ! -d "$protobuf_build_dir" ]; then
	mkdir -p $protobuf_build_dir
fi

if [ ! -d "$protobuf_test_dir" ]; then
	mkdir -p $protobuf_test_dir
fi

if [ ! -d "$protobuf_test_types_dir" ]; then
	mkdir -p $protobuf_test_types_dir
fi

if [[ $clean_build == "yes" ]]; then
	echo "clean protobuf_install..."
	rm $OUT_DIR -rf
	rm $protobuf_test_dir -rf
	rm $protobuf_test_types_dir -rf
else
	echo "build protobuf... "
	echo "protobuf VERSION=$protobuf_version platform_type=$platform_type"
	if [ -d  "$protobuf_install_dir" ]; then
		pushd $protobuf_build_dir
		if [[ $protobuf_version == "3.5.0" ]]; then
			cmake -Dprotobuf_MODULE_COMPATIBLE=ON -DCMAKE_INSTALL_PREFIX=$protobuf_install_dir -Dprotobuf_BUILD_SHARED_LIBS=ON -Dprotobuf_BUILD_TESTS=off $PROTOBUF_3_5/cmake/ || exit 1
		elif [[ $protobuf_version == "3.21.12" ]]; then
			cmake -Dprotobuf_MODULE_COMPATIBLE=ON -DCMAKE_INSTALL_PREFIX=$protobuf_install_dir -Dprotobuf_BUILD_SHARED_LIBS=ON -Dprotobuf_BUILD_TESTS=off $PROTOBUF_3_21_12 || exit 1
		fi	
		make -j8
		make install
		popd
	fi
fi

if [ -d  "$protobuf_test_dir" ]; then
	pushd $protobuf_test_dir
	cmake -DPLANT_FORAMT=$platform_type ..
	make
	popd
fi

if [ -d  "$protobuf_test_types_dir" ]; then
	pushd $protobuf_test_types_dir
	cmake -DPLANT_FORAMT=$platform_type ..
	make
	popd
fi
