cmake_minimum_required(VERSION 3.16)

project(Sign_up VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# ... your existing code ...

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Sign_up
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        style.qrc
        user.h user.cpp
        createacc.h createacc.cpp createacc.ui
        appwindow.h appwindow.cpp appwindow.ui











    )

    # ────────────────────────────────────────────────
    # ADD THIS BLOCK (or just the target_include_directories line)
    target_include_directories(Sign_up PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include"
    )

    # Optional: more robust version for Debug/Release subfolders (if errors persist)
    # target_include_directories(Sign_up PRIVATE
    #     "${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include"
    #     "$<$<CONFIG:Debug>:${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include_Debug>"
    #     "$<$<CONFIG:Release>:${CMAKE_CURRENT_BINARY_DIR}/Sign_up_autogen/include_Release>"
    # )
    # ────────────────────────────────────────────────

# ... rest of your file ...
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Sign_up APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Sign_up SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Sign_up
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Sign_up
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Charts
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
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
