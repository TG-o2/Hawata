cmake_minimum_required(VERSION 3.16)

project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sign_up
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        style.qrc
        user.h user.cpp
        createacc.h createacc.cpp createacc.ui
        appwindow.h appwindow.cpp appwindow.ui
        connection.h connection.cpp
        Docking.h Docking.cpp
    )

    target_include_directories(Sign_up PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include"
    )

else()
    if(ANDROID)
        add_library(Sign_up SHARED
            ${PROJECT_SOURCES}
            style.qrc
            user.h user.cpp
            createacc.h createacc.cpp createacc.ui
            appwindow.h appwindow.cpp appwindow.ui
            connection.h connection.cpp
        )
    else()
        add_executable(Sign_up
            ${PROJECT_SOURCES}
            style.qrc
            user.h user.cpp
            createacc.h createacc.cpp createacc.ui
            appwindow.h appwindow.cpp appwindow.ui
            connection.h connection.cpp
        )
    endif()
endif()

target_link_libraries(Sign_up PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Sign_up)
endif()
set_target_properties(Sign_up PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Sign_up
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Sign_up)
endif()
