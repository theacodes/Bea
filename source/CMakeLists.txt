############################################
#
#  Asteroids CMake
#
############################################
cmake_minimum_required( VERSION 2.8 )

project( Bea )

############################################
# Source files
############################################
set( BEA_SOURCES
	main.cpp
	StringHash.h
	PropertyContainer.h
	PrintAny.h
)

############################################
# Exes
############################################

# main program
add_executable( BeaTest ${BEA_SOURCES} )
target_link_libraries( BeaTest ${LIBRARIES} )

#####################################
# Windows stuff
######################################
#WINDOWS (MSVC)
if(WIN32)
	if(MSVC)
#	    set_target_properties( Asteroids
#	        PROPERTIES WIN32_EXECUTABLE true )
	endif()
endif()