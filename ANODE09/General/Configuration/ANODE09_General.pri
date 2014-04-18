isEmpty(ANODE09_General_PRI_INCLUDED) {
  message ( loading ANODE09_General.pri )
}
# **InsertLicense** code
# -----------------------------------------------------------------------------
# ANODE09_General prifile
#
# \file    ANODE09_General.pri
# \author     wieke
# \date    2014-04-18
#
# Modules created for the ANODE09 competition.
#
# -----------------------------------------------------------------------------

# include guard against multiple inclusion
isEmpty(ANODE09_General_PRI_INCLUDED) {

ANODE09_General_PRI_INCLUDED = 1

# -- System -------------------------------------------------------------

include( $(MLAB_MeVis_Foundation)/Configuration/SystemInit.pri )

# -- Define local PACKAGE variables -------------------------------------

PACKAGE_ROOT    = $$(MLAB_ANODE09_General)
PACKAGE_SOURCES = "$$(MLAB_ANODE09_General)"/Sources

# Add package library path
LIBS          += -L"$${PACKAGE_ROOT}"/lib

# -- Projects -------------------------------------------------------------

# NOTE: Add projects below to make them available to other projects via the CONFIG mechanism

# You can use this example template for typical projects:
#MLMyProject {
#  CONFIG_FOUND += MLMyProject
#  INCLUDEPATH += $${PACKAGE_SOURCES}/ML/MLMyProject
#  win32:LIBS += MLMyProject$${d}.lib
#  unix:LIBS += -lMLMyProject$${d}
#}

# -- ML Projects -------------------------------------------------------------

# -- Inventor Projects -------------------------------------------------------

# -- Shared Projects ---------------------------------------------------------

# End of projects ------------------------------------------------------------

}