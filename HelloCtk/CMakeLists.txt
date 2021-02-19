cmake_minimum_required(VERSION 3.5)

#指定工程
project(HelloCtk LANGUAGES CXX)

#指定为动态库
option(BUILD_SHARED_LIBS "Build CTK Plugin" ON)

#CTK安装路径
set(CTK_INSTALL_PATH D:/Git/CTK-install)

# 添加 CTK 相关的头文件搜索路径
include_directories(${CTK_INSTALL_PATH}/include/ctk-0.1)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../CTKmaster/Libs/PluginFramework)

# 查找 CTK 相关的库文件
find_library(CORE_LIB CTKCore ${CTK_INSTALL_PATH}/lib/ctk-0.1 NO_DEFAULT_PATH)
find_library(FRAMWORK_LIB CTKPluginFramework ${CTK_INSTALL_PATH}/lib/ctk-0.1
NO_DEFAULT_PATH)
link_libraries(${CORE_LIB} ${FRAMWORK_LIB})
# 设置自动生成 moc 文件
set(CMAKE_AUTOMOC ON)

#查找需要的 Qt 库文件
find_package(Qt5Core)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HelloCtk
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(HelloCtk SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(HelloCtk
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(HelloCtk PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
