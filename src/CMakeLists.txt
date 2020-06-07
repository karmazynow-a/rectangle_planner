SET( APP_NAME AG_proj )

project(${APP_NAME} CXX C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# Check GAlib availability
find_library(GALIB ga ${GALIB_DIR}/ga)
IF(NOT EXISTS ${GALIB})
  MESSAGE(FATAL_ERROR "Cannot find GAlib library")
ENDIF(NOT EXISTS ${GALIB})

SET( APP_HEADERS 
    ${CMAKE_SOURCE_DIR}/Board.h
    ${CMAKE_SOURCE_DIR}/BoardList.h
    ${CMAKE_SOURCE_DIR}/BoardLocation.h
    ${CMAKE_SOURCE_DIR}/ObjectiveHelper.h
    ${CMAKE_SOURCE_DIR}/utility.h )

SET( APP_SOURCES 
    ${CMAKE_SOURCE_DIR}/main.cpp 
    ${CMAKE_SOURCE_DIR}/BoardList.cpp
    ${CMAKE_SOURCE_DIR}/BoardLocation.cpp
    ${CMAKE_SOURCE_DIR}/ObjectiveHelper.cpp
    ${CMAKE_SOURCE_DIR}/utility.cpp )


ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} ${APP_HEADERS} ) 

target_compile_options(${APP_NAME} PRIVATE -fpermissive)

TARGET_LINK_LIBRARIES(${APP_NAME} ${GALIB})