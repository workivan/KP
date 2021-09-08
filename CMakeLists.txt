cmake_minimum_required(VERSION 3.20)
project(C__)

set(CMAKE_CXX_STANDARD 17)


set(SFML_INCLUDE_DIR "/home/ivan/CLionProjects/C++/libs/SFML/include")
set(SFML_LIBRARY_DIR "/home/ivan/CLionProjects/C++/libs/SFML/lib")
set(SFML_DIR "/home/ivan/CLionProjects/C++/libs/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5 COMPONENTS system window graphics network audio)

include_directories(hdr)
add_subdirectory(src)

set(BINARY ${CMAKE_PROJECT_NAME})
target_link_libraries(${BINARY}run sfml-graphics sfml-window sfml-system)