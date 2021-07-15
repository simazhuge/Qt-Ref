QT += core
QT -= gui
TARGET = EmbedCTK
CONFIG += console
TEMPLATE = app
# CTK 安装路径
CTK_INSTALL_PATH = D:/Git/CTK-install
# CTK 插件相关库所在路径（例如：CTKCore.lib、CTKPluginFramework.lib）
CTK_LIB_PATH = $$CTK_INSTALL_PATH/lib/ctk-0.1

# CTK 插件相关头文件所在路径（例如：ctkPluginFramework.h）
CTK_INCLUDE_PATH = $$CTK_INSTALL_PATH/include/ctk-0.1
# CTK 插件相关头文件所在路径（主要因为用到了 service 相关东西）
CTK_INCLUDE_FRAMEWORK_PATH = D:/Git/CTK/Libs/PluginFramework
LIBS += -L$$CTK_LIB_PATH -lCTKCore -lCTKPluginFramework
INCLUDEPATH += $$CTK_INCLUDE_PATH \
$$CTK_INCLUDE_FRAMEWORK_PATH
SOURCES += main.cpp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
#    mainwindow.cpp

#HEADERS += \
#    mainwindow.h

#FORMS += \
#    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
