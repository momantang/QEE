cmake_minimum_required(VERSION 3.5)
set(DCMAKE_TOOLCHAIN_FILE "D:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
include("D:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(QEEMain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
#        mainwindow.ui

        b23mw.h
        b23mw.cpp
        #b23mw.ui

       

        cv/camera.cpp
        cv/camera.h
        cv/mindvisioncamera.h
        cv/mindvisioncamera.cpp

        cv/cvmainwindow.h 
        cv/cvmainwindow.cpp
        #cv/cvmainwindow.ui
        cv/aboutwidget.h
        cv/aboutwidget.cpp
cv/cvaction.h cv/cvaction.cpp
        #cv/aboutwidget.ui
        utils.h utils.cpp

        #include/CameraApi.h
        #include/CameraApiLoad.h
        #include/CameraDefine.h
        #include/CameraGrabber.h
        #include/CameraImage.h
        #include/CameraStatus.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QEEMain
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES})
   # add_executable(QEEMain ${PROJECT_SOURCES})

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QEEMain APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QEEMain SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QEEMain
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QEEMain PRIVATE Qt${QT_VERSION_MAJOR}::Widgets opencv_ml opencv_dnn opencv_dpm opencv_hdf)

set_target_properties(QEEMain PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QEEMain)
endif()
