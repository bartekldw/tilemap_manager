cmake_minimum_required(VERSION 3.10)
set(project_name main)
project(${project_name})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    gui/Textbox.cpp
    gui/Button.cpp
    gui/Menu.cpp
    src/TextManager.cpp
    src/Builder.cpp
    src/Tilemap.cpp
    loader/Settings.cpp
    add/tinyfiledialogs.c
    add/clip/clip.cpp
    add/clip/clip_x11.cpp
    main.cpp
)
if(WIN32)
    message(STATUS "Build for Windows")
    list(APPEND SOURCES add/clip/clip_win.cpp)
    list(APPEND SOURCES add/clip/clip_win_wic.cpp)
    list(APPEND SOURCES add/clip/clip_win_bmp.cpp)
elseif(UNIX)
    message(STATUS "Build for Unix/Linux")
    find_package(X11 REQUIRED)
    list(APPEND SOURCES add/clip/clip_x11.cpp)
    link_libraries(${X11_LIBRARIES})
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(${project_name} ${SOURCES})
target_link_libraries(${project_name} sfml-graphics sfml-window sfml-system)
target_include_directories(${project_name} PRIVATE add)
if(UNIX)
    target_include_directories(${project_name} PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(${project_name} ${X11_LIBRARIES} xcb)
endif()
