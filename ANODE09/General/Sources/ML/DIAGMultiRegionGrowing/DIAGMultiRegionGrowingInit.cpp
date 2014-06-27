//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-06-27
*/
//----------------------------------------------------------------------------------


// Local includes
#include "DIAGMultiRegionGrowingSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include "mlLibraryInitMacros.h"

// Include all module headers ...
#include "mlMultiRegionGrowing.h"


ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int DIAGMultiRegionGrowingInit()
{
  MultiRegionGrowing::initClass();
  // Add initClass calls from all other modules here.

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(DIAGMultiRegionGrowingInit)