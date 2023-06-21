cmake_minimum_required(VERSION 3.25)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


add_executable(sudoku main.cpp SudokuEngine.h SudokuEngine.cpp Button.cpp Button.h)

set(SFML_DIR "D:\\456\\lib\\sfml\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(sudoku sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)

