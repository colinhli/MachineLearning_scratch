cmake_minimum_required (VERSION 2.8)
project(ml)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/)

include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories("${PROJECT_SOURCE_DIR}/build/include/eigen3")

add_definitions(-std=c++11)
add_definitions(-O2)

SUBDIRLIST(SUBDIRS ${PROJECT_SOURCE_DIR}/examples)
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()