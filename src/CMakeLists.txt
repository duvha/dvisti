cmake_minimum_required(VERSION 3.16)

project(Dvisti VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        DX21/dx21_operator.cpp
        DX21/dx21_voice.cpp
        DX21/dx21.cpp
        data.cpp
        rtmidi/RtMidi.cpp
)

qt_add_executable(Dvisti
        ${PROJECT_SOURCES}
)

target_link_libraries(Dvisti PRIVATE Qt6::Widgets)

add_compile_definitions(__UNIX_JACK__)
#add_compile_definitions(__LINUX_ALSA__)
target_link_libraries(Dvisti PRIVATE jack)
#target_link_libraries(Dvisti PRIVATE asound)
#target_link_libraries(Dvisti PRIVATE pthread)

set_target_properties(Dvisti PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

