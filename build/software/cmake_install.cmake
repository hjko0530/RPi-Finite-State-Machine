# Install script for directory: /home/pi/LightDance-RPi/controller/software

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/LightDance-RPi/controller/bin/list")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/LightDance-RPi/controller/bin" TYPE EXECUTABLE FILES "/home/pi/LightDance-RPi/controller/build/software/list")
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/list")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/LightDance-RPi/controller/bin/load")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/LightDance-RPi/controller/bin" TYPE EXECUTABLE FILES "/home/pi/LightDance-RPi/controller/build/software/load")
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/load")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/LightDance-RPi/controller/bin/parttest")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/LightDance-RPi/controller/bin" TYPE EXECUTABLE FILES "/home/pi/LightDance-RPi/controller/build/software/parttest")
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/parttest")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/LightDance-RPi/controller/bin/playerctl")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/LightDance-RPi/controller/bin" TYPE EXECUTABLE FILES "/home/pi/LightDance-RPi/controller/build/software/playerctl")
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/playerctl")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/pi/LightDance-RPi/controller/bin/player")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/pi/LightDance-RPi/controller/bin" TYPE EXECUTABLE FILES "/home/pi/LightDance-RPi/controller/build/software/player")
  if(EXISTS "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/home/pi/LightDance-RPi/controller/bin/player")
    endif()
  endif()
endif()

