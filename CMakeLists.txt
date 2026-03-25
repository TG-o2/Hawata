cmake_minimum_required(VERSION 3.16)
project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Charts PrintSupport)

# List of project sources
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
    fancyui.qrc
    images.qrc
    style.qrc
)

# Create executable
qt_add_executable(Sign_up
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Link Qt libraries
target_link_libraries(Sign_up PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Charts
    Qt6::PrintSupport
)

# macOS bundle settings
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Sign_up)
# endif()
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

# Finalize executable (Qt6)
qt_finalize_executable(Sign_up)
