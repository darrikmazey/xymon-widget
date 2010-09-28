
#
# xymon_widget.pro
# DarmaSoft, LLC.
#
# 2010.09.25
#

message("building xymon_widget")

TEMPLATE = app
TARGET =

QT +=

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

CONFIG +=
QT +=

FORMS = 
HEADERS =

HEADERS += mainwindow.h \
						settingsdialog.h \
						application.h

SOURCES = xymon_widget.cpp \
					mainwindow.cpp \
					settingsdialog.cpp \
					application.cpp
