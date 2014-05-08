# -----------------------------------------------------------------------------
# _MLFilterLabelByVolume project profile
#
# \file
# \author     wieke
# \date    2014-05-08
# -----------------------------------------------------------------------------


TEMPLATE   = lib

TARGET     = _MLFilterLabelByVolume

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

DEFINES += _MLFILTERLABELBYVOLUME_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    _MLFilterLabelByVolumeInit.h \
    _MLFilterLabelByVolumeSystem.h \
    mlFilterLabelByVolumeOutputImageHandler.h \
    mlFilterLabelByVolume.h \

SOURCES += \
    _MLFilterLabelByVolumeInit.cpp \
    mlFilterLabelByVolumeOutputImageHandler.cpp \
    mlFilterLabelByVolume.cpp \