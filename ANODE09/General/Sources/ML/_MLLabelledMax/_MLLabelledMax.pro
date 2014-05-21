# -----------------------------------------------------------------------------
# _MLLabelledMax project profile
#
# \file
# \author     wieke
# \date    2014-05-21
# -----------------------------------------------------------------------------


TEMPLATE   = lib

TARGET     = _MLLabelledMax

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

DEFINES += _MLLABELLEDMAX_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    _MLLabelledMaxInit.h \
    _MLLabelledMaxSystem.h \
    mlLabelledMax.h \

SOURCES += \
    _MLLabelledMaxInit.cpp \
    mlLabelledMax.cpp \