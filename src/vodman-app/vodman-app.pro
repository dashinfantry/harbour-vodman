# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-vodman

QT += dbus

CONFIG += sailfishapp

DISTFILES += harbour-vodman.desktop
DISTFILES += icons/cover.svg
DISTFILES += icons/icon.svg
DISTFILES += icons/tape.png

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
#TRANSLATIONS += ../../translations/harbour-vodman-de.ts



DBUS_INTERFACES += ../../dbus/org.duckdns.jgressmann.vodman.xml




SOURCES += harbour-vodman.cpp
SOURCES += VMQuickVodDownloadModel.cpp
SOURCES += VMQuickVodDownload.cpp

HEADERS += VMQuickVodDownloadModel.h
HEADERS += VMQuickVodDownload.h



desktop.files = harbour-vodman.desktop
desktop.path = /usr/share/applications
INSTALLS += desktop

qml.path = /usr/share/$${TARGET}/qml
qml.files = qml/*
INSTALLS += qml

icons.path = /usr/share/$${TARGET}/icons
icons.files = icons/cover.svg icons/icon.svg icons/tape.png
INSTALLS += icons


CONFIG += link_pkgconfig
#PKGCONFIG += nemotransferengine-qt5 sailfishapp
PKGCONFIG += sailfishapp


include(../../common.pri)
LIBS += -L../vodman-lib -lvodman
