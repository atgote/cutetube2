QT += core network
QT -= gui
CONFIG += plugin
TARGET = cutetube2-wenoo
TEMPLATE = lib

HEADERS += \
    wenooplugin.h \
    wenoorequest.h

SOURCES += \
    wenoorequest.cpp

symbian {
    TARGET.UID3 = 0xF23BA41E
    TARGET.CAPABILITY += NetworkServices ReadUserData WriteUserData
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.EPOCHEAPSIZE = 0x20000 0x8000000
    TARGET.EPOCSTACKSIZE = 0x14000

    INCLUDEPATH += ../src
    HEADERS += \
        ../src/resourcesrequest.h \
        ../src/serviceplugin.h
    
    vendorinfo += "%{\"Stuart Howarth\"}" ":\"Stuart Howarth\""
    wenoo_deployment.pkg_prerules += vendorinfo

    config.sources = "$$TARGET".json
    config.path = !:/cutetube2/plugins

    lib.sources = "$$TARGET".dll
    lib.path = !:/sys/bin

    stub.sources = "$$TARGET".qtplugin
    stub.path = !:/cutetube2/plugins

    DEPLOYMENT.display_name = cuteTube2 Wenoo.net
    DEPLOYMENT += \
        wenoo_deployment \
        config \
        lib \
        stub

} else:contains(MEEGO_EDITION,harmattan) {
    INCLUDEPATH += ../src
    HEADERS += \
        ../src/resourcesrequest.h \
        ../src/serviceplugin.h
    
    config.files = "$$TARGET".json
    config.path = /opt/cutetube2/plugins
    
    contentaction.files = "$$TARGET".xml
    contentaction.path = /usr/share/contentaction

    target.path = /opt/cutetube2/plugins
    
    INSTALLS += \
        target \
        config \
        contentaction

} else:unix {
    INCLUDEPATH += /usr/include/cutetube2
    HEADERS += \
        /usr/include/cutetube2/resourcesrequest.h \
        /usr/include/cutetube2/serviceplugin.h
    
    config.files = "$$TARGET".json
    config.path = /opt/cutetube2/plugins

    target.path = /opt/cutetube2/plugins
    
    INSTALLS += \
        target \
        config
}
