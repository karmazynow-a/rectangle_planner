SET( APP_NAME AG_proj_test )

project(${APP_NAME} CXX C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# Check GAlib availability
find_library(GALIB ga ${GALIB_DIR}/ga)
IF(NOT EXISTS ${GALIB})
  MESSAGE(FATAL_ERROR "Cannot find GAlib library")
ENDIF(NOT EXISTS ${GALIB})

SET( BOARD_HEADERS 
    ${CMAKE_SOURCE_DIR}/../AG/Board/Board.h
    ${CMAKE_SOURCE_DIR}/../AG/Board/BoardList.h
    ${CMAKE_SOURCE_DIR}/../AG/Board/BoardLocation.h )

SET( TOOLS_HEADERS 
    ${CMAKE_SOURCE_DIR}/../AG/AGtools/ObjectivePenalty.h )

SET( APP_HEADERS 
    ${BOARD_HEADERS}
    ${TOOLS_HEADERS} )

SET( BOARD_SOURCES 
    ${CMAKE_SOURCE_DIR}/../AG/Board/BoardList.cpp
    ${CMAKE_SOURCE_DIR}/../AG/Board/BoardLocation.cpp )

SET( TOOLS_SOURCES 
    ${CMAKE_SOURCE_DIR}/../AG/AGtools/ObjectivePenalty.cpp )

SET( APP_SOURCES 
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${BOARD_SOURCES}
    ${TOOLS_SOURCES})

ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} ${APP_HEADERS} ) 

target_compile_options(${APP_NAME} PRIVATE -fpermissive)

TARGET_LINK_LIBRARIES(${APP_NAME} ${GALIB})