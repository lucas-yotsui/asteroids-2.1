cmake_minimum_required(VERSION 3.14...3.22)
# --------- Project ---------
project(Asteroides VERSION 1.0 LANGUAGES CXX)
set(PROJECT_BIN "asteroides")
include(cmake/all.cmake)
include(ExternalProject)

ExternalProject_Add(SFML
    GIT_REPOSITORY		https://github.com/SFML/SFML.git
    GIT_TAG				2.6.x
	SOURCE_DIR			"${CMAKE_SOURCE_DIR}/build/sfml-src"
	BINARY_DIR			"${CMAKE_SOURCE_DIR}/build/sfml-build"
	CONFIGURE_COMMAND	""
	BUILD_COMMAND		""
	INSTALL_COMMAND		""
	TEST_COMMAND		""
)

option(BUILD_SHARED_LIBS "set external libraries as static(off) or shared(on)" OFF)

set(TEXTURES
	textures/full-ship.png
	textures/sequencia-explosao.png
	textures/tiro.png
	textures/asteroide-pequeno.png
	textures/asteroide-medio.png
	textures/asteroide-grande.png
	textures/life-levels.png
	textures/background.png
)

set(FONT
	fonts/Starjedi.ttf
)

foreach(ASSET ${TEXTURES})
	file(COPY ${ASSET} DESTINATION ${CMAKE_BINARY_DIR}/textures)
endforeach()

file(COPY ${FONT} DESTINATION ${CMAKE_BINARY_DIR}/fonts)

add_subdirectory(source)

add_executable(${PROJECT_BIN} app/main.cpp)

if (WIN32 OR WIN64)
	target_link_libraries(${PROJECT_BIN} ${PROJECT_NAME} project_options project_warnings sfml-graphics)
else()
	target_link_libraries(${PROJECT_BIN} ${PROJECT_NAME} project_options project_warnings sfml-graphics pthread X11)
endif()

install(TARGETS ${PROJECT_NAME})