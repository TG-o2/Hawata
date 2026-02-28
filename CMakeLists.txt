cmake_minimum_required(VERSION 3.16)
project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)

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
    connection.h
    connection.cpp
    Docking.h
    Docking.cpp
    boats.h
    boats.cpp
    company.h
    company.cpp
    manage.h
    manage.cpp
    style.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sign_up
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        .gitignore
    )
else()
    if(ANDROID)
        add_library(Sign_up SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Sign_up
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Sign_up PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

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
