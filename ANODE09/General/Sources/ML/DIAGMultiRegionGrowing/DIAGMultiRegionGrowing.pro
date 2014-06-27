# -----------------------------------------------------------------------------
# DIAGMultiRegionGrowing project profile
#
# \file
# \author  Wieke
# \date    2014-06-27
# -----------------------------------------------------------------------------


TEMPLATE   = lib

TARGET     = DIAGMultiRegionGrowing

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

DEFINES += DIAGMULTIREGIONGROWING_EXPORTS

# Enable ML deprecated API warnings. To completely disable the deprecated API, change WARN to DISABLE.
DEFINES += ML_WARN_DEPRECATED

HEADERS += \
    DIAGMultiRegionGrowingInit.h \
    DIAGMultiRegionGrowingSystem.h \
    mlMultiRegionGrowingOutputImageHandler.h \
    mlMultiRegionGrowing.h \

SOURCES += \
    DIAGMultiRegionGrowingInit.cpp \
    mlMultiRegionGrowingOutputImageHandler.cpp \
    mlMultiRegionGrowing.cpp \