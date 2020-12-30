cmake_minimum_required(VERSION 3.8)

project(INFOGA-Bonus)

#Set the sfml source directory to the extern folder and find sfml
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/SFML/lib/cmake/SFML" CACHE FILEPATH "Filepath for SFML")
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/glm/cmake/glm" CACHE FILEPATH "Filepath for GLM")
find_package(GLM REQUIRED)

add_executable("${PROJECT_NAME}" 
                "main.cpp"
                "ConvexHullBase.cpp"
                "ConvexHullBase.h"
                "JarvisMarch.cpp"
                "JarvisMarch.h"
                "TestConvexHull.cpp"
                "TestConvexHull.h")
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")

#Add sfml library links to the main executable
target_link_libraries("${PROJECT_NAME}" sfml-graphics sfml-window sfml-system)
#Add glm libraries to the main executable
target_link_libraries("${PROJECT_NAME}" glm::glm)