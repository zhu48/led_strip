# from 3.9.6 onwards, checking IPO has a cleaner syntax
cmake_minimum_required(VERSION 3.9.6)

####################################
# Set Project-Level Configurations #
####################################

project(led_strip CXX)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

# set language standards
set(CMAKE_CXX_STANDARD                  17)
set(CMAKE_CXX_STANDARD_REQUIRED         TRUE)
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES   "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

# set the policy to enable inter-procedural optimization if available
if(POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif()
if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    include(CheckIPOSupported)
    message(STATUS "Determining inter-procedural optimization support")
    check_ipo_supported(RESULT CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    if(CMAKE_INTERPROCEDURAL_OPTIMIZATION)
        message(STATUS "Inter-procedural optimization enabled")
    else()
        message(STATUS "Inter-procedural optimization disabled")
    endif()
    set(
        CMAKE_INTERPROCEDURAL_OPTIMIZATION
            ${CMAKE_INTERPROCEDURAL_OPTIMIZATION}
        CACHE INTERNAL "" FORCE
    )
endif()

######################
# Derive Directories #
######################

get_filename_component(REPO_CONTAINING_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(LEDS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(LEDS_IPP_DIR ${LEDS_INC_DIR}/ipp)
set(LEDS_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

#########################
# Gather Target Sources #
#########################

set(
    LEDS_INC_FILES
        ${LEDS_INC_DIR}/doom_fire.hpp
        ${LEDS_INC_DIR}/pattern_fill.hpp
        ${LEDS_INC_DIR}/ripple.hpp
        ${LEDS_INC_DIR}/vop.hpp
        ${LEDS_INC_DIR}/ws2812b.hpp
)
set(
    LEDS_INC_FILES
        ${LEDS_IPP_DIR}/doom_fire.ipp
        ${LEDS_IPP_DIR}/pattern_fill.ipp
        ${LEDS_IPP_DIR}/ripple.ipp
        ${LEDS_IPP_DIR}/ws2812b.ipp
)
set(
    LEDS_SRC_FILES
        ${LEDS_SRC_DIR}/main.cpp
        ${LEDS_SRC_DIR}/ws2812b.cpp
)

#######################
# Gather Dependencies #
#######################

add_subdirectory(${REPO_CONTAINING_DIR}/RPP/build ${CMAKE_CURRENT_BINARY_DIR}/rpp)

################################
# Configure Application Target #
################################

add_executable(
    leds_app
        ${LEDS_INC_FILES}
        ${LEDS_IPP_FILES}
        ${LEDS_SRC_FILES}
)
target_include_directories(
    leds_app
    PUBLIC
        ${LEDS_INC_DIR}
        ${LEDS_IPP_DIR}
)
target_link_libraries(leds_app PUBLIC rpp)
target_link_libraries(leds_app PUBLIC periph)
