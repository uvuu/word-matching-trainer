cmake_minimum_required(VERSION 3.14)

project(word-matching-trainer LANGUAGES CXX)

# This is required to include auto-generated(aka MOC) headers
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

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
    qt_add_executable(word-matching-trainer
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(word-matching-trainer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(word-matching-trainer
          ${PROJECT_SOURCES}
        )
    endif()
endif()

# The generator expressions to evaluate the need for QML debug mode
target_compile_definitions(word-matching-trainer
  PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_compile_options(word-matching-trainer
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_link_libraries(word-matching-trainer
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

# [CMAKE_]COMPILE_WARNING_AS_ERROR is only available since version 3.24
#set_property(TARGET word-matching-trainer PROPERTY COMPILE_WARNING_AS_ERROR ON)
#set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
#set_target_properties(word-matching-trainer PROPERTIES COMPILE_WARNING_AS_ERROR ON)
