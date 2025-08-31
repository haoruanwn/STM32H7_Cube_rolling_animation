file(GLOB USER_DRIVER_SOURCES
        Src/*.c
        Src/*.cpp
)

add_library(user_driver STATIC
        ${USER_DRIVER_SOURCES}
)


target_include_directories(user_driver
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Src"

)

target_link_libraries(user_driver
        PRIVATE
        stm32cubemx
)