cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(../..)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

file(GLOB MACRO_FILES
	"mac/*.mac"
)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES
	"dat/*.dat"
)

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})


add_custom_target(Simulation DEPENDS sim)
