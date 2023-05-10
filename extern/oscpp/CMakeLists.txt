project(OSCPP
        VERSION
            1.0.0
        LANGUAGES
            CXX
        DESCRIPTION
            "CPP Adapter to send OSC Messages over the network"
        )
cmake_minimum_required(VERSION 3.25)

add_library(OSCPP INTERFACE)
target_include_directories(OSCPP
        INTERFACE
            "${CMAKE_CURRENT_SOURCE_DIR}/source/include")