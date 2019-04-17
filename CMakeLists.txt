cmake_minimum_required(VERSION 3.4.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

project (iNOBEngine)

file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.h")


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/ PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/ PREFIX "Source Files" FILES ${SOURCES})

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(lua 5.1 REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(opengl REQUIRED)
find_package(unofficial-box2d CONFIG REQUIRED)

include_directories( ${LUA_INCULDE_DIR} )
set ( PROJECT_LINK_LIBS SDL2::SDL2 SDL2::SDL2main opengl32 glu32 SDL2::SDL2_image sol2 nlohmann_json nlohmann_json::nlohmann_json unofficial::box2d::Box2D ${LUA_LIBRARIES})
SET(BASEPATH "${CMAKE_SOURCE_DIR}")

add_library(iNOBEngine ${SOURCES} ${HEADERS})
target_link_libraries(iNOBEngine PRIVATE ${PROJECT_LINK_LIBS} )

enable_testing()
find_package(GTest MODULE REQUIRED)

include_directories( src/ ${LUA_INCULDE_DIR})

add_executable(Tests ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(Tests PRIVATE ${PROJECT_LINK_LIBS} iNOBEngine GTest::GTest GTest::Main)

set_property(TARGET iNOBEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET Tests PROPERTY CXX_STANDARD 17)