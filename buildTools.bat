@echo off

cd ZTG_Tools
cd ZTG_SpriteEditor
mkdir bin
cd bin
cmake .. -G "MinGW Makefiles"
make
cd ..
cd ..
cd .. 
cd .. 