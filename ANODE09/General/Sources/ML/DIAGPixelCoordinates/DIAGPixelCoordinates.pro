# -----------------------------------------------------------------------------
# DIAGPixelCoordinates project profile
#
# \file
# \author  Wieke
# \date    2014-06-05
# -----------------------------------------------------------------------------


TEMPLATE   = lib

TARGET     = DIAGPixelCoordinates

DESTDIR    = ../../../lib
DLLDESTDIR = ../../../lib

# Set high warn level (warn 4 on MSVC)
WARN = HIGH

# Add used projects here (see included pri files below for available projects)
CONFIG += dll ML

MLAB_PACKAGES += ANODE09_General \
                 MeVisLab_Standard

# make sure that this file is included after CONFIG and MLAB_PACKAGES
include ($(MLAB_MeVis_Foundation)/Configuration/IncludePackages.pri)

DEFINES += DIAGPIXELCOORDINATES_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    DIAGPixelCoordinatesInit.h \
    DIAGPixelCoordinatesSystem.h \
    mlPixelCoordinates.h \

SOURCES += \
    DIAGPixelCoordinatesInit.cpp \
    mlPixelCoordinates.cpp \