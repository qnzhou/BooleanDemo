# This file is part of mesh boolean demo. Copyright (c) 2016 by Qingnan Zhou
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Set compiler
SET(CMAKE_C_COMPILER "clang")
SET(CMAKE_CXX_COMPILER "clang++")
#SET(CMAKE_C_COMPILER "gcc")
#SET(CMAKE_CXX_COMPILER "g++")

SET(LIBIGL_INC "~/Research/libigl/include")
SET(EIGEN_INC "/opt/local/include/eigen3")

PROJECT(cgal_test)

# Set build type.
SET(CMAKE_BUILD_TYPE Release)

# Create 64 bits binary.  32 bits support is dropped.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")

# Include customized FindPackage scripts
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

IF (NOT CGAL_FOUND)
    IF (DEFINED ENV{CGAL_PATH} AND NOT DEFINED ENV{CGAL_DIR})
        SET(CGAL_DIR $ENV{CGAL_PATH})
    ENDIF (DEFINED ENV{CGAL_PATH} AND NOT DEFINED ENV{CGAL_DIR})
    FIND_PACKAGE(CGAL)
ENDIF (NOT CGAL_FOUND)

# Inlclude CGAL
IF(CGAL_FOUND)
    SET(BACKUP_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    INCLUDE(${CGAL_USE_FILE})
    SET(CMAKE_CXX_FLAGS ${BACKUP_CXX_FLAGS})
    ADD_DEFINITIONS(-DWITH_CGAL)
    LIST(APPEND DEPENDENT_LIBS ${CGAL_LIBRARIES})
ELSE(CGAL_FOUND)
    MESSAGE(WARNING "CGAL missing.  Skipping CGAL convex hull support")
ENDIF(CGAL_FOUND)

# Include Eigen
INCLUDE_DIRECTORIES(${EIGEN_INC})

# Include libigl
INCLUDE_DIRECTORIES(${LIBIGL_INC})

ADD_EXECUTABLE(cgal_boolean src/cgal_boolean.cpp)
TARGET_LINK_LIBRARIES(cgal_boolean ${DEPENDENT_LIBS})

ADD_EXECUTABLE(libigl_boolean src/libigl_boolean.cpp)
TARGET_LINK_LIBRARIES(libigl_boolean ${DEPENDENT_LIBS})
