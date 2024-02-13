@echo off

cd Examples/ZTG_FatBall
mkdir bin
cd bin
cmake .. -G "MinGW Makefiles"
make
cd ../..
cd ZTG_Snake
mkdir bin
cd bin
cmake .. -G "MinGW Makefiles"
make
cd ../../..