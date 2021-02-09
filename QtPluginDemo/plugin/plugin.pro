#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../PluginDemo
HEADERS         = \
    CustomWidget.h \
    CustomWidgetCollection.h \
    CustomWidgetCollectionInterface.h \
    CustomWidgetInterface.h \
    buttonplugin.h
SOURCES         = \
    CustomWidget.cpp \
    CustomWidgetCollection.cpp \
    buttonplugin.cpp
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = echoplugin.json

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/echoplugin/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
