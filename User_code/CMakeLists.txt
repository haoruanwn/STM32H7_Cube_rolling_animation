file(GLOB SOURCES "Src/*.cpp")
add_library(user_code STATIC ${SOURCES})


target_include_directories(user_code
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Inc"

)

target_link_libraries(user_code
        PRIVATE
        stm32cubemx
        user_driver
)