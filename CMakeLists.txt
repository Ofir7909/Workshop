cmake_minimum_required(VERSION 3.17.2)

project(WORKSHOP)

# Create static library
set(SOURCES

    src/client/Application.h
    src/client/Window.cpp
    src/client/Input.cpp
    src/client/Application.cpp
    src/client/panels/PanelManager.cpp

    src/core/rendering/Shader.cpp
    src/core/Time.cpp

    src/nodes/BaseNode.cpp
)
add_library(workshop STATIC ${SOURCES})

target_compile_features(workshop PUBLIC cxx_std_20)
target_include_directories(workshop PUBLIC src/)

# Libraries
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(workshop PUBLIC 
    glad::glad
    glfw
    imgui::imgui
    spdlog::spdlog_header_only
    glm::glm
)

#resources
add_custom_target(copy_res_folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_BINARY_DIR}/res
)
add_dependencies(workshop copy_res_folder)

#Create Executable
add_executable(workshop_main
    src/client/main.cpp
)
target_link_libraries(workshop_main PUBLIC workshop)

#enable_testing()
#add_subdirectory(tests)
