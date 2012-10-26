############################################
#
#  Bea CMake
#
############################################
cmake_minimum_required( VERSION 2.8 )

project( Bea )

############################################
# Source files
############################################
set( BEA_TEST_SOURCES
    BeaTestApplication.h
    Cat.h
    main.cpp
)

############################################
# Exes
############################################

# main program
add_executable( BeaTest ${BEA_TEST_SOURCES} )
target_link_libraries( BeaTest Bea ${LIBRARIES} )

#####################################
# Windows stuff
######################################
#WINDOWS (MSVC)
if(WIN32)
    if(MSVC)
#       set_target_properties( BeaTest
#           PROPERTIES WIN32_EXECUTABLE true )
    endif()
endif()