PROJECT(Kiwi)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE (CheckIncludeFileCXX)

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_SOURCE_DIR}/CMake/Packages )

# dependencies
FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(BZip2 REQUIRED)
FIND_PACKAGE(Qt4 REQUIRED)
# optional dependencies

# project version
SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 1 )
SET( ${PROJECT_NAME}_BUILD_LEVEL 0 )

IF( NOT CMAKE_BUILD_TYPE )
  SET( CMAKE_BUILD_TYPE "RelWithDebInfo" )
ENDIF()

# options

# add sources
SET(Kiwi_SRCS
  src/Kiwi.cpp
  src/Repository.cpp

  src/bsdiff.c
  src/bspatch.c

  src/main.cpp
)

# common includes and libraries
INCLUDE_DIRECTORIES(
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIRS})
LINK_DIRECTORIES(${QT_LIBRARY_DIRS})
LINK_LIBRARIES(${QT_LIBRARIES})

QT4_WRAP_UI(Kiwi_SRCS
  resources/kiwi.ui
  resources/kiwi_about.ui
)
QT4_WRAP_CPP(Kiwi_SRCS include/Kiwi.h)

#CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/KiwiConfig.h.cmake ${CMAKE_SOURCE_DIR}/include/KiwiConfig.h )

LINK_DIRECTORIES(${BZip2_LIBRARY_DIRS})
LINK_LIBRARIES(bz2)

ADD_EXECUTABLE(bin/${PROJECT_NAME} ${Kiwi_SRCS} )
TARGET_LINK_LIBRARIES(bin/${PROJECT_NAME} ${Kiwi_LIBRARIES})
