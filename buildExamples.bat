@echo off

cd Examples/ZTG_FatBall
mkdir bin
cd bin
cmake .. -G "MinGW Makefiles"
make