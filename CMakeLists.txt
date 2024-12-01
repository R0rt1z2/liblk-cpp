cmake_minimum_required(VERSION 3.25)
project(liblk VERSION 1.0.0 DESCRIPTION "Library for handling Lk images")

include(GNUInstallDirs)

add_library(liblk
        liblk/LkExtHeader.cpp
        liblk/LkHeader.cpp
        liblk/LkImage.cpp
        liblk/LkPartition.cpp
)

set_target_properties(liblk PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER "liblk/include/liblk.h"
)

target_include_directories(liblk PUBLIC liblk/include)

install(TARGETS liblk
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/liblk
)

configure_file(liblk.pc.in ${CMAKE_BINARY_DIR}/liblk.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/liblk.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)