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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
else()
    if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
    else()
	add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
    endif()
endif()

# The generator expressions to evaluate the need for QML debug mode
target_compile_definitions(${PROJECT_NAME}
  PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
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
