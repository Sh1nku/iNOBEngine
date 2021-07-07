cmake_minimum_required(VERSION 3.16.3)

project (iNOBEngine)

file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
file(GLOB_RECURSE TEST_HEADERS "tests/*.h")
file(GLOB_RECURSE EXAMPLES_ASTEROID_SOURCES "examples/AsteroidAvoidanceGame/src/*.cpp")
file(GLOB_RECURSE EXAMPLES_ASTEROID_MANIFEST "examples/AsteroidAvoidanceGame/src/*.manifest")
file(GLOB_RECURSE EXAMPLES_ASTEROID_HEADERS "examples/AsteroidAvoidanceGame/src/*.h")

if (MSVC)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/ PREFIX "Source Files" FILES ${SOURCES} ${HEADERS})
	add_definitions(/bigobj)
endif (MSVC)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
set ( PROJECT_LINK_LIBS CONAN_PKG::sdl2_image CONAN_PKG::sdl2 CONAN_PKG::lua CONAN_PKG::sol2 CONAN_PKG::nlohmann_json CONAN_PKG::opengl CONAN_PKG::glu CONAN_PKG::box2d CONAN_PKG::imgui CONAN_PKG::glm CONAN_PKG::cef_binaries)

add_library(iNOBEngine SHARED ${SOURCES} ${HEADERS})
target_link_libraries(iNOBEngine PRIVATE ${PROJECT_LINK_LIBS} )
set_target_properties(iNOBEngine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_executable(Tests ${TEST_SOURCES} ${TEST_HEADERS})
target_include_directories(Tests PRIVATE src/)
target_link_libraries(Tests PRIVATE iNOBEngine ${PROJECT_LINK_LIBS} CONAN_PKG::gtest)

message("${CONAN_LIBS}")

add_executable(AsteroidAvoidanceGame ${EXAMPLES_ASTEROID_SOURCES} ${EXAMPLES_ASTEROID_HEADERS})
target_include_directories(AsteroidAvoidanceGame PRIVATE src/)
target_link_libraries(AsteroidAvoidanceGame PRIVATE ${PROJECT_LINK_LIBS} iNOBEngine)

set_property(TARGET iNOBEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET Tests PROPERTY CXX_STANDARD 17)
set_property(TARGET AsteroidAvoidanceGame PROPERTY CXX_STANDARD 17)
