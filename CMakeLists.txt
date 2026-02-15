cmake_minimum_required(VERSION 3.16)

project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# FIND QT MODULES BEFORE CREATING TARGET
# -------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Sql)

# -------------------------
# SOURCES
# -------------------------
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    user.h
    user.cpp
    product.h
    product.cpp
    createacc.h
    createacc.cpp
    createacc.ui
    appwindow.h
    appwindow.cpp
    appwindow.ui
    style.qrc
)

# -------------------------
# CREATE EXECUTABLE
# -------------------------
if(Qt6_FOUND)
    qt_add_executable(Sign_up
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )

    target_include_directories(Sign_up PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include"
    )

    target_link_libraries(Sign_up PRIVATE
        Qt6::Widgets
        Qt6::Charts
        Qt6::Sql
    )

    qt_finalize_executable(Sign_up)
else()
    add_executable(Sign_up ${PROJECT_SOURCES})
    target_link_libraries(Sign_up PRIVATE Qt5::Widgets)
endif()
