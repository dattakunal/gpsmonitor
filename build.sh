#!/bin/bash

CWD=$(dirname ${BASH_SOURCE[0]})
BUILD_DIR=${CWD}/build

build() {
    local dir=$1
    local cwd=$(pwd)
    mkdir -p ${dir}
    cd $dir
    cmake ..
    make all
    cd ${cwd}
}

build ${BUILD_DIR}
