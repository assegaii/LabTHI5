QT += core gui widgets testlib

CONFIG += c++17 testlib


# Добавляем все исходники из src
SOURCES += \
    ../src/mainwindow.cpp \
    ../src/trackdialog.cpp \
    ../src/addeditdialog.cpp \
    tst_mainwindow.cpp

# Добавляем все заголовочные файлы
HEADERS += \
    ../src/trackdialog.h \
    ../src/track.h \
    ../src/mainwindow.h \
    ../src/addeditdialog.h  # Если используются другие заголовочные файлы

# Добавляем все формы .ui, если они используются в тестах
FORMS += \
    ../src/trackdialog.ui \
    ../src/mainwindow.ui \
    ../src/addeditdialog.ui  # Если используются другие формы .ui

INCLUDEPATH += $$PWD/../src

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

