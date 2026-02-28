cmake_minimum_required(VERSION 3.16)

project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

<<<<<<< HEAD
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

=======
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)

# -------------------------
# FIND QT MODULES BEFORE CREATING TARGET
# -------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Sql)

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
    style.qrc

)

# ... your existing code ...

>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sign_up
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
<<<<<<< HEAD
        style.qrc
        user.h user.cpp
        createacc.h createacc.cpp createacc.ui
        appwindow.h appwindow.cpp appwindow.ui
        connection.h connection.cpp
        Docking.h Docking.cpp
=======
        company.h company.cpp



>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
    )

    target_include_directories(Sign_up PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include"
    )

<<<<<<< HEAD
=======
    target_link_libraries(Sign_up PRIVATE
        Qt6::Widgets
        Qt6::Charts
        Qt6::Sql
    )


# ... rest of your file ...
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Sign_up APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
else()
    if(ANDROID)
        add_library(Sign_up SHARED
            ${PROJECT_SOURCES}
<<<<<<< HEAD
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
=======
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Sign_up
            ${PROJECT_SOURCES}
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
        )
    endif()
endif()

<<<<<<< HEAD
target_link_libraries(Sign_up PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

=======
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
>>>>>>> 71f93a09f10e0ea93fabf2f98f463c8f24f647a1
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
