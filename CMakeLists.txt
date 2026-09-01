cmake_minimum_required(VERSION 3.16)

project(Qt-Scenario-Manager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/scenarioManager.cpp)

set(HEADERS
    src/scenarioManager.h)

set(DATA
    data/default_scenario.json
    data/test_mission.json)

qt_add_executable(Qt-Scenario-Manager
    ${SOURCES}
    ${HEADERS}
    ${DATA}
)

target_link_libraries(Qt-Scenario-Manager PRIVATE
    Qt6::Widgets
)