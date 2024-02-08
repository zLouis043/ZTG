cmake_minimum_required(VERSION 3.27)
project(ZTG)
set(PROJECT_VERSION 1.0.0)
set(API_VERSION 100)


set(ztg_public_headers  Fonts/font8x8_basic.h 
                        Fonts/8x8font.h
                        ZTG_Defines.h
                        ZTG_Vectors.h 
                        ZTG_Core.h
                        ZTG_Draw.h
                        ZTG_Utils.h
                        ZTG_Objects.h
                        ZTG_Collisions.h
                        ZTG.h)

set(ztg_sources Fonts/ib8x8u/ib8x8u.c
                Fonts/icl8x16/icl8x16u.c
                ZTG_Vectors.c 
                ZTG_Core.c 
                ZTG_Draw.c 
                ZTG_Utils.c 
                ZTG_Objects.c 
                ZTG_Collisions.c)

add_library(ZTG STATIC ${ztg_sources} ${ztg_public_headers})

if (WIN32)
    set_target_properties(ZTG PROPERTIES
            LINK_FLAGS "/WHOLEARCHIVE"
    )
elseif (APPLE)
    set_target_properties(ZTG PROPERTIES
            LINK_FLAGS "-Wl,-all_load"
    )
else ()
    set_target_properties(ZTG PROPERTIES
            LINK_FLAGS "-Wl,--whole-archive"
    )
endif ()

