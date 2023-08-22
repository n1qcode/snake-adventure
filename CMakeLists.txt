cmake_minimum_required(VERSION 3.7)
project(Snake_Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake_Game main.cpp)

if(APPLE OR UNIX)
    SET(PLATFORM_SPECIFIC_LIBS "-lpthread")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

    include_directories(/usr/local/include)
else()
    set(SFML_DIR "C:/Libraries/SFML/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Snake_Game sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
endif()