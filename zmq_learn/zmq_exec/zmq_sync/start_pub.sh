#! /bin/bash

CURR_DIR=$(pwd)
EXEC_DIR=$CURR_DIR/../output

pushd $EXEC_DIR

echo "正在启动订阅者..."
for a in 1 2 3 4 5 6 7 8 9 10; do
    ./syncsub &
done
echo "正在启动发布者..."
./syncpub

popd