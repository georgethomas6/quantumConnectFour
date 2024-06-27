cmake_minimum_required(VERSION 3.28)
project(Connect_Four)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
add_executable(Connect_Four
        GameLogic.cpp
        Headers/GameLogic.h
        main.cpp
        cFourGraphics.cpp
        Headers/cFourGraphics.h
        Headers/Game.h
)
target_link_libraries(Connect_Four sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
