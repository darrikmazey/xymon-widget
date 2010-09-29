
#
# xymon_widget.pro
# DarmaSoft, LLC.
#
# 2010.09.25
#

message("building xymon_widget")

TEMPLATE = app
TARGET = xymon_widget

QT += network

DEPENDPATH += . src
INCLUDEPATH += . src ui

QMAKE_LIBDIR +=
LIBS +=

# setting RELEASE environment variable builds release target
RELEASEENV = $$(RELEASE)
isEmpty(RELEASEENV) {
	CONFIG += debug
	CONFIG -= release
} else {
	CONFIG += release
	CONFIG -= debug
}

# build directories
OBJECTS_DIR = build
MOC_DIR = moc
VPATH += src
UI_DIR = ui

# strip debug output on release
QMAKE_CXXFLAGS_RELEASE += -D QT_NO_DEBUG_OUTPUT

CONFIG(debug) {
	message("building debug target")
} else {
	message("building release target")
}

PREFIX=debian/xymon-widget
desktop.path = $$PREFIX/usr/share/applications/hildon-home
desktop.files = xymon_widget.desktop

images.path = $$PREFIX/opt/xymon-widget/images
images.files = xymon_red.png xymon_blue.png xymon_green.png xymon_yellow.png

target.path = $$PREFIX/usr/lib/hildon-desktop
INSTALLS += target desktop images


CONFIG +=
QT +=

FORMS = 
HEADERS =

HEADERS += qmaemo5homescreenadaptor.h \
						xymonwidget.h \
						settingsdialog.h

SOURCES = qmaemo5homescreenadaptor.cpp \
					xymon_widget.cpp \
					xymonwidget.cpp \
					settingsdialog.cpp

