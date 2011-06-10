CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE (CheckIncludeFileCXX)

IF(DEFINED CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

PROJECT(Kiwi)

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_SOURCE_DIR}/CMake/Packages )

IF(WIN32)
  SET( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:/Workspace/Build/Qt4.7.3 )
	SET( CMAKE_LIBRARY_PATH
    ${CMAKE_LIBRARY_PATH}
    C:/Workspace/Build/bzip2/Release)
	SET( CMAKE_INCLUDE_PATH
    ${CMAKE_INCLUDE_PATH}
    C:/Workspace/Build/bzip2/include)

  ADD_DEFINITIONS("-D_CRT_SECURE_NO_WARNINGS")
ENDIF()

# dependencies
FIND_PACKAGE(BZip2 REQUIRED)
FIND_PACKAGE(Qt4 REQUIRED)
# optional dependencies

# project version
SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 1 )
SET( ${PROJECT_NAME}_BUILD_LEVEL 0 )

# options

# add sources
SET(Kiwi_SRCS
  include/Entry.h
  include/Kiwi.h
  include/md5.hpp
  include/Pixy.h
  include/Repository.h
  include/Tarball.h
  include/Utility.h
  include/getlogin.h

  src/Kiwi.cpp
  src/Repository.cpp

  src/bsdiff.cpp
  src/bspatch.cpp

  src/main.cpp
)

# common includes and libraries
INCLUDE_DIRECTORIES(
  include
  ${CMAKE_CURRENT_BINARY_DIR}
  ${BZIP2_INCLUDE_DIR}
)


ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIRS})
QT4_WRAP_UI(Kiwi_UI_SRCS
  resources/kiwi.ui
  resources/kiwi_about.ui
)
QT4_ADD_RESOURCES(Kiwi_QRC_SRCS resources/media.qrc)
QT4_WRAP_CPP(Kiwi_MOC_SRCS include/Kiwi.h)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

LINK_DIRECTORIES(${QT_LIBRARY_DIRS} ${BZIP2_LIBRARY_DIRS})
LINK_LIBRARIES(${QT_LIBRARIES} ${BZIP2_LIBRARIES})

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
IF(WIN32)
  SET(Karazeh_SRCS ${Karazeh_SRCS} src/getlogin.cpp)
  ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${Kiwi_SRCS} ${Kiwi_MOC_SRCS} ${Kiwi_QRC_SRCS} ${Kiwi_UI_SRCS})
ELSE()
  ADD_EXECUTABLE(${PROJECT_NAME} ${Kiwi_SRCS}  ${Kiwi_MOC_SRCS} ${Kiwi_QRC_SRCS} ${Kiwi_UI_SRCS} )
ENDIF()
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Kiwi_LIBRARIES})
