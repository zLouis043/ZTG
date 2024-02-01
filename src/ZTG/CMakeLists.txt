
add_library(ZTG STATIC
        Fonts/font8x8_basic.h
        Fonts/8x8font.h
        Fonts/ib8x8u/ib8x8u.c
        Fonts/icl8x16/icl8x16u.c
        ZTG_Vectors.c
        ZTG_Vectors.h
        ZTG_Core.c
        ZTG_Core.h
        ZTG_Defines.h
        ZTG_Draw.c
        ZTG_Draw.h
        ZTG_Utils.c
        ZTG_Utils.h
        ZTG.h
        ZTG_Objects.c
        ZTG_Objects.h
        ZTG_Collisions.c
        ZTG_Collisions.h)

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