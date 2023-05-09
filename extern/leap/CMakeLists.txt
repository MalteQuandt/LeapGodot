cmake_minimum_required(VERSION 3.20)
project(LeapMotionSDK
        VERSION
            0.0.2
        LANGUAGES
            CXX
        DESCRIPTION
            "Basic Leap Motion Setup to use it with CMake")

message(STATUS "Creating Leap Library")

# as the leap sdk does not support, we throw an error if msvc aka visual studio compiler is not used
if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"))
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER_ID} is not supported! Please use visual studio!")
endif()

# if there are any errors, please refer to this page>
# https://developer-archive.leapmotion.com/documentation/v2/cpp/devguide/Leap_SDK_Overview.html#c

option(ARCHITECTURE_IS_X64 "Is the system that this project is build on x64?" ON)

if(ARCHITECTURE_IS_X64)
    message(STATUS "build the system using x64 libraries")
    set(ARCHITECTURE "x64")
else()
    message(STATUS "build the system using x86 libraries")
    set(ARCHITECTURE "x86")
endif()

# create the library
add_library(LeapMotionSDK SHARED IMPORTED GLOBAL)

# set the include directory for the leap lib
target_include_directories(LeapMotionSDK
        INTERFACE
            "${CMAKE_CURRENT_SOURCE_DIR}/include")

# only for windows
set_target_properties("LeapMotionSDK"
        PROPERTIES
            IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCHITECTURE}/Leap.lib")

target_compile_features(${CMAKE_PROJECT_NAME}
        PRIVATE
            cxx_std_11)

message(STATUS "Define the Libraries and copy the DLL's")

# define the location of the dll (can later be moved, just has to be found during runtime in PATH)
set_target_properties(LeapMotionSDK
        PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/${ARCHITECTURE}/Leap.dll")

# move the file
configure_file("${PROJECT_SOURCE_DIR}/lib/${ARCHITECTURE}/Leap.dll" # input file
        "${CMAKE_BINARY_DIR}/" # output dir
        COPYONLY)

if(DEFINED INSTALL_DIR)
    install(
            FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCHITECTURE}/Leap.dll
            DESTINATION ${INSTALL_DIR}/leap
    )
endif()

message(STATUS "Successfully build the Leap-SDK!")
