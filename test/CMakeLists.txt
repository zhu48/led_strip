# from 3.9.6 onwards, checking IPO has a cleaner syntax
cmake_minimum_required(VERSION 3.9.6)

####################################
# Set Project-Level Configurations #
####################################

project(algo_test CXX)

set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

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

get_filename_component(REPO_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
get_filename_component(REPO_CONT_DIR ${REPO_ROOT_DIR} DIRECTORY)

#####################
# Configure Testing #
#####################

find_package(Catch2 REQUIRED)

enable_testing()

set(LEDS_INC_DIR ${REPO_ROOT_DIR}/include)
set(LEDS_IPP_DIR ${LEDS_INC_DIR}/ipp)

# compile vector operations test executable
add_executable(
    test_vop
        ${CMAKE_CURRENT_SOURCE_DIR}/test_vop.cpp
)
target_include_directories(
    test_vop
    PUBLIC
        ${LEDS_INC_DIR}
        ${LEDS_IPP_DIR}
)
target_link_libraries(test_vop Catch2::Catch2)

add_test(NAME vector_ops COMMAND test_vop --out=${CMAKE_CURRENT_LIST_DIR}/test_vop.log)
