cmake_minimum_required(VERSION 3.14)

project(word-matching-trainer LANGUAGES CXX)

# This is required to include auto-generated(aka MOC) headers
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# To find out why we need to call find_package() twice here read the following page
# https://doc.qt.io/qt-6/cmake-qt5-and-qt6-compatibility.html.
# In short: this is due to versioned target names prior to Qt 5.15.
# And yes, seems we load the same package twice but with different names (QT and Qt${QT_VERSION_MAJOR}).
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 REQUIRED)

# The idea of the QT_VERSION_6_OR_HIGHER variable is to allow mock the 5th version of Qt.
# For example, we may pass it with OFF value to build project in a way Qt5 project would build.
# For more information, see usage of QT_VERSION_6_OR_HIGHER in the project.
if(NOT DEFINED QT_VERSION_6_OR_HIGHER AND ${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    set(QT_VERSION_6_OR_HIGHER ON)
endif()

# Set the name for the general qml module
set(QML_URI com.uvuu.qml)

# Headers are needed here to be visible in the project tree
set(PROJECT_SOURCES
    QML/qml.qrc
    res/res.qrc

    src/main.cpp
    src/data_reader.h
    src/data_reader.cpp
    src/exercise.h
    src/exercise.cpp
    src/options.h
    src/options.cpp
    src/performer.h
    src/performer.cpp
    src/task_handler.h
    src/task_handler.cpp

    src/QML/exercise_view_data.h
    src/QML/exercise_view_data.cpp
)

if(QT_VERSION_6_OR_HIGHER)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

    # The advanced way to register custom qml types using QML_ELEMENT and etc.
    # instead of qmlRegister*() functions family.
    if(${QT_VERSION_MINOR} GREATER_EQUAL 2)
        qt_add_qml_module(${PROJECT_NAME}
            URI ${QML_URI}
            VERSION 1.0
        )
    else()
        set_target_properties(${PROJECT_NAME}
            PROPERTIES
                QT_QML_MODULE_VERSION 1.0
                QT_QML_MODULE_URI ${QML_URI}
            )
        # It is necessary to include this directory since the file with registrations will be
        # created in the 'build' directory and it includes files without relative paths.
        target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/QML)
        qt_qml_type_registration(${PROJECT_NAME})
    endif()
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
    else()
        add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
    endif()

    # This is an alternative to the modern way of registering a QML type and is suitable
    # for the 5th Qt version. Obviously it relays on qmlRegister*() functions.
    target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/QML/qml_registrar.cpp)

    # The old way to tell CMake where the Android build files are(also see QT_ANDROID_PACKAGE_SOURCE_DIR)
    set(ANDROID_PACKAGE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/res/android" CACHE INTERNAL "")
endif()

# To make the build system to use AndroidManifest.xml and other project-specified resourses
# we need to point where they are. QT_ANDROID_PACKAGE_SOURCE_DIR is available since Qt6,
# previous versions have to use ANDROID_PACKAGE_SOURCE_DIR.
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/res/android"
)

# The generator expressions to evaluate the need for QML debug mode
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
        $<$<BOOL:${QT_VERSION_6_OR_HIGHER}>:QT_VERSION_6_OR_HIGHER>
        QML_URI="${QML_URI}"
)
# Treat warnings as errors(preferably use [CMAKE_]COMPILE_WARNING_AS_ERROR)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
# [CMAKE_]COMPILE_WARNING_AS_ERROR is only available since version 3.24
#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_WARNING_AS_ERROR ON)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
)

# Allows us to include any files in 'src' directory without putting 'src/' in front of it.
# See '#include "exercise.h"' in QML/exercise_view_data.h.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
