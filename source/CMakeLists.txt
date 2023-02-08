add_library(${PROJECT_NAME} 
engine.cpp 
base-entity.cpp 
player.cpp 
asteroid.cpp 
shot.cpp 
graphical-interface.cpp 
animation.cpp 
explosion.cpp 
graphical-asteroid.cpp 
graphical-player.cpp
graphical-shot.cpp
hud.cpp
camera.cpp
game.cpp
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
SOVERSION 1
VERSION 1.0.0
)

target_include_directories(${PROJECT_NAME}
PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)

target_link_libraries(
${PROJECT_NAME}
PRIVATE project_options
project_warnings
)