# Install script for directory: /usr/src/pinetime-hypnos/zephyr

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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/root/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/arch/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/lib/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/soc/arm/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/boards/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/subsys/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/drivers/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/app/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/cmsis/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/nordic/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/lvgl/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/littlefs/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/mcumgr/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/segger/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/tinycbor/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/modules/tinycrypt/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/kernel/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/cmake/flash/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/cmake/usage/cmake_install.cmake")
  include("/usr/src/pinetime-hypnos/build-hypnos/zephyr/cmake/reports/cmake_install.cmake")

endif()

