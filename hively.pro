include($$PWD/../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/hively

HEADERS += decoderhivelyfactory.h \
           decoder_hively.h \
           hivelyhelper.h \
           hivelymetadatamodel.h
    
SOURCES += decoderhivelyfactory.cpp \
           decoder_hively.cpp \
           hivelyhelper.cpp \
           hivelymetadatamodel.cpp \
           libhively/hvl_replay.c

INCLUDEPATH += $$PWD/libhively

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libhively.so
}
