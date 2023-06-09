# SPDX-License-Identifier: Unlicense

cmake_minimum_required( VERSION 3.25 )

# Main project information
project( LeapGodot
        LANGUAGES
            CXX
        VERSION
            1.0.0
        DESCRIPTION
            "Godot Nodes that can receive data from a leap motion controller, and one that is able to send osc data to a sound dome."
        )

set(CMAKE_COMPILE_WARNING_AS_ERROR OFF) # disable the 'bad' paradigm

message( STATUS "Using CMake ${CMAKE_VERSION}" )

# LIB_ARCH is the architecture being built. It is set to the build system's architecture.
# For macOS, we build a universal library (both arm64 and x86_64).
set( LIB_ARCH ${CMAKE_SYSTEM_PROCESSOR} )

# Add paths to modules
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/" )

# LIB_DIR is where the actual library ends up. This is used in both the build directory and the
# install directory and needs to be consistent with the paths in the gdextension file.
#   e.g. linux.release.x86_64 = "lib/Linux-x86_64/libGDExtensionTemplate.so"
set( LIB_DIR "lib/${CMAKE_SYSTEM_NAME}-${LIB_ARCH}" )

# Require out-of-source builds
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )

if ( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in the source directory. Please use a build subdirectory." )
endif()

# (optionally) load variables from a config file
set(ConfigFilePath ".cmakeconfig" CACHE STRING "The Path to the Config file! If this is not set, no config file is assumed to exist!")
if(NOT (${ConfigFilePath} STREQUAL ""))
    message(STATUS "Reading Config File ${ConfigFilePath}")
    include(Utils)
    ReadConfigFile(${ConfigFilePath})
endif()

# Turn on link time optimization for everything
set( CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON )

# Output compile commands to compile_commands.json (for debugging CMake issues)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


# Create our library
add_library( ${PROJECT_NAME} SHARED )

target_compile_features( ${PROJECT_NAME}
    PRIVATE
        cxx_std_23
)

target_sources( ${PROJECT_NAME}
        PRIVATE
        # leap motion
            "src/leap/LeapController.cpp"
            "src/leap/helper/InteractionBox.cpp"
            "src/leap/helper/Frame.cpp"
        # hands
            "src/leap/helper/hands/Hand.cpp"
            "src/leap/helper/hands/HandList.cpp"
        # gestures
            "src/leap/helper/gestures/Gesture.cpp"
            "src/leap/helper/gestures/GestureList.cpp"
        # audio
            "src/audio/AudioController.cpp"
        # osc client
            "src/osc/OSCLeapClient.cpp"
        # godot bindings
            "RegisterExtension.cpp"
        )

target_include_directories( ${PROJECT_NAME}
        PRIVATE
            "${CMAKE_SOURCE_DIR}/include"
        )


message( STATUS "Building ${PROJECT_NAME} for ${LIB_ARCH} on ${CMAKE_SYSTEM_NAME}")

# BUILD_OUTPUT_DIR is where we put the resulting library (in the build directory)
set( BUILD_OUTPUT_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/" )

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
        CXX_VISIBILITY_PRESET
            hidden
        VISIBILITY_INLINES_HIDDEN
            true
        RUNTIME_OUTPUT_DIRECTORY
            "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
        LIBRARY_OUTPUT_DIRECTORY
            "${BUILD_OUTPUT_DIR}/${LIB_DIR}"
)

if( NOT DEFINED CMAKE_DEBUG_POSTFIX )
    set_target_properties( ${PROJECT_NAME}
        PROPERTIES
            DEBUG_POSTFIX "-d"
    )
endif()

# Warnings
include( CompilerWarnings )

# Create and include version info file from git
include( GitVersionInfo )

if(NOT DEFINED INSTALL_DIR)
    # Install library and extension file in ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
    set( INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/" )
endif()
message( STATUS "Install directory: ${INSTALL_DIR}")

install( TARGETS ${PROJECT_NAME}
    LIBRARY
        DESTINATION ${INSTALL_DIR}/${LIB_DIR}
    RUNTIME
        DESTINATION ${INSTALL_DIR}/${LIB_DIR}
)

add_subdirectory( templates )

# ccache
# Turns on ccache if found
include( ccache )

# Formatting
# Adds a custom target to format all the code at once
include( ClangFormat )

# godot-cpp
# From here: https://github.com/godotengine/godot-cpp
if ( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/extern/godot-cpp/Makefile" )
    message(
        FATAL_ERROR
            "[${PROJECT_NAME}] The godot-cpp submodule was not downloaded. Please update submodules: git submodule update --init --recursive."
    )
endif()

set( GODOT_CPP_SYSTEM_HEADERS ON CACHE BOOL "" FORCE )

add_subdirectory(extern)

set_target_properties( godot-cpp
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden    # visibility needs to be the same as the main library
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        godot-cpp
        LeapMotionSDK
        OSCPack
)