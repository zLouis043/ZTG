cmake_minimum_required(VERSION 3.26.4)
project(ZTG_Snake)

include_directories(../../src)
add_subdirectory(../../src/ZTG src/ZTG/lib)
add_executable(${PROJECT_NAME} 
        GameLoop.h
        GameLoop.c
        entryPoint.h
        entryPoint.c
        main.c
        ../../src/ZTG/resources/resource.rc)
set(LINK_FLAGS ${LINK_FLAGS} "-Wl,-whole-archive")
target_link_libraries(${PROJECT_NAME} ZTG)
