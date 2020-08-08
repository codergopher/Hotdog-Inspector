cmake_minimum_required (VERSION 3.0)

project (Hotdog_Inspector)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -m64 -g -Wall -I include -I C:/SDL2-w64/include -L C:/SDL2-w64/lib")

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (Hotdog_Inspector ${source_files})

target_link_libraries(Hotdog_Inspector SDL2 SDL2main SDL2_image)