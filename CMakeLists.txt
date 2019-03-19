cmake_minimum_required(VERSION 3.4.0)
project (iNOBEngine)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.h")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/ PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/ PREFIX "Source Files" FILES ${SOURCES})

set ( PROJECT_LINK_LIBS SDL2.lib SDL2main.lib lua5.1.lib opengl32.lib glu32.lib)
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
link_directories( ../Libraries/SDL2-2.0.4/lib/x86 ../Libraries/lua-5.1.5)
include_directories( ../Libraries/SDL2-2.0.4/include ../Libraries/lua-5.1.5/include ../Libraries/Sol2 ../Libraries/JSON)

add_library(iNOBEngine ${SOURCES} ${HEADERS})
target_link_libraries(iNOBEngine ${PROJECT_LINK_LIBS} )

include_directories( src/ )
link_directories( ../Libraries/SDL2-2.0.4/lib/x86 ../Libraries/lua-5.1.5)
add_executable(Tests ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(Tests ${PROJECT_LINK_LIBS} iNOBEngine gtest_main)