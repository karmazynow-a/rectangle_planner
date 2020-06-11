SET( APP_NAME AG_proj )

project(${APP_NAME} CXX C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# Check GAlib availability
find_library(GALIB ga ${GALIB_DIR}/ga)
IF(NOT EXISTS ${GALIB})
  MESSAGE(FATAL_ERROR "Cannot find GAlib library")
ENDIF(NOT EXISTS ${GALIB})

SET( BOARD_HEADERS 
    ${CMAKE_SOURCE_DIR}/Board/Board.h
    ${CMAKE_SOURCE_DIR}/Board/BoardList.h
    ${CMAKE_SOURCE_DIR}/Board/BoardLocation.h )

SET( TOOLS_HEADERS 
    ${CMAKE_SOURCE_DIR}/utility.h
    ${CMAKE_SOURCE_DIR}/AGtools/AGtools.h 
    ${CMAKE_SOURCE_DIR}/AGtools/Objective.h
    ${CMAKE_SOURCE_DIR}/AGtools/ObjectivePenalty.h )

SET( APP_HEADERS 
    ${BOARD_HEADERS}
    ${TOOLS_HEADERS} )

SET( BOARD_SOURCES 
    ${CMAKE_SOURCE_DIR}/Board/BoardList.cpp
    ${CMAKE_SOURCE_DIR}/Board/BoardLocation.cpp )

SET( TOOLS_SOURCES 
    ${CMAKE_SOURCE_DIR}/utility.cpp
    ${CMAKE_SOURCE_DIR}/AGtools/AGtools.cpp
    ${CMAKE_SOURCE_DIR}/AGtools/Objective.cpp
    ${CMAKE_SOURCE_DIR}/AGtools/ObjectivePenalty.cpp )

SET( APP_SOURCES 
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${BOARD_SOURCES}
    ${TOOLS_SOURCES} )

ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} ${APP_HEADERS} ) 

target_compile_options(${APP_NAME} PRIVATE -fpermissive)

TARGET_LINK_LIBRARIES(${APP_NAME} ${GALIB})