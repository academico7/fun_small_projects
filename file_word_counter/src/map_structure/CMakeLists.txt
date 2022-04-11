cmake_minimum_required(VERSION 3.2)
project(map_structure)

set(SOURCE_FILES
    wordcounter.h
    wordpair.hdsada
)

add_library(map_structure SHARED STATIC ${SOURCE_FILES})

install(TARGETS map_structure DESTINATION ${INSTALL_LIB_DIR})
#install(FILES wordpair.h DESTINATION ${INSTALL_LIB_DIR})