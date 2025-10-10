cmake_minimum_required(VERSION 3.16)

project(practica_3_info_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica_3_info_2 main.cpp
    codificar.h codificar.cpp
    auxiliares.h auxiliares.cpp
    decodificar.h decodificar.cpp)

include(GNUInstallDirs)
install(TARGETS practica_3_info_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
