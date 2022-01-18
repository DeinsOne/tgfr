#!/bin/sh

rm -rf tmp
mkdir tmp
cd tmp

##########################################################
## Install moudles
install_module() {
    git clone --depth=1 https://github.com/$1/$2.git

    cd $2
    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4
    cmake --build . --target install

    cd ../../
}
##########################################################

install_module reo7sp tgbot-cpp
install_module gabime spdlog

cd ../
rm -rf tmp
