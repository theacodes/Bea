############################################
#
#  Asteroids CMake
#
############################################
cmake_minimum_required( VERSION 2.8 )

project( Bea )

############################################
# Bea Library Source files
############################################

set( BEA_LIB_SOURCES
    AppState.h
    AppStateManager.h
    Event.h
    EventListener.h
    EventManager.h
    EventSpy.h
    Object.h
    ObjectViewCommon.h
    PhoenixEvents.h
    PrintAny.h
    PropertyContainer.h
    StringHash.h
    View.h
    EventManager.cpp
)

############################################
# Source files
############################################
set( BEA_TEST_SOURCES
	main.cpp
)

############################################
# Libs
############################################

add_library( Bea STATIC ${BEA_LIB_SOURCES} )

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
#	    set_target_properties( Asteroids
#	        PROPERTIES WIN32_EXECUTABLE true )
	endif()
endif()