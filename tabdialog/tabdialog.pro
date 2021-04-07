QT += widgets
requires(qtConfig(listwidget))

HEADERS       = tabdialog.h \
    TabColseBtn.h
SOURCES       = main.cpp \
                TabColseBtn.cpp \
                tabdialog.cpp
# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/dialogs/tabdialog
INSTALLS += target

RESOURCES += \
    image.qrc
