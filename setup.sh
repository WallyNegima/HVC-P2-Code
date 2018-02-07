#!/bin/bash
sudo apt-get update
sudo apt-get -y install libi2c-dev
sudo apt-get -y install cmake
sudo apt-get -y install libsqlite3-dev

git clone git://git.drogon.net/wiringPi
cd wiringPi/
./build
cd ../

git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c
cmake .
make
sudo make install
cd ../

git clone https://github.com/m-mizutani/libfluent.git
cd libfluent/
cmake .
make
sudo make install
cd ../

sudo /sbin/ldconfig -v
cp ./99-serial.rules /etc/udev/rules.d
