cmake_minimum_required(VERSION 3.8)

project(INFOGA-Bonus)

add_executable(${PROJECT_NAME}
                "main.cpp"
                "ConvexHullBase.cpp"
                "ConvexHullBase.h"
                "JarvisMarch.cpp"
                "JarvisMarch.h"
                "TestConvexHull.cpp"
                "TestConvexHull.h"
                "DivideConquer.cpp"
                "DivideConquer.h"
                "PerformanceTests.h"
                "PerformanceTests.cpp"
                )
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

#Add sfml library links to the main executable
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window sfml-system)