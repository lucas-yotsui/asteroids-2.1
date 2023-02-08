cmake_minimum_required(VERSION 3.14...3.22)
# --------- Project ---------
project(Asteroides VERSION 1.0 LANGUAGES CXX)
set(PROJECT_BIN "asteroides")
include(cmake/all.cmake)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

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
target_link_libraries(${PROJECT_BIN} ${PROJECT_NAME} project_options project_warnings sfml-graphics)