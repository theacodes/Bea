############################################
#
#  Bea CMake
#
############################################
cmake_minimum_required( VERSION 2.8 )

project( Bea )

############################################
# Bea Library Source files
############################################

FILE (GLOB SOURCES *.cpp *.h tmx-parser/*.cpp tmx-parser/*.h tmx-parser/base64/* tmx-parser/tinyxml/* tmx-parser/zlib/*)

set( BEA_LIB_SOURCES ${SOURCES} ${HEADERS})

############################################
# Libs
############################################

add_library( Bea STATIC ${BEA_LIB_SOURCES} )