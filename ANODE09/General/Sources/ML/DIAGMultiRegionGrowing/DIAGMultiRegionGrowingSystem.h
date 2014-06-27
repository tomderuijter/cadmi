//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-06-27
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGMultiRegionGrowingSystem_H
#define __DIAGMultiRegionGrowingSystem_H


// DLL export macro definition.
#ifdef DIAGMULTIREGIONGROWING_EXPORTS
  // Use the DIAGMULTIREGIONGROWING_EXPORT macro to export classes and functions.
  #define DIAGMULTIREGIONGROWING_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define DIAGMULTIREGIONGROWING_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // __DIAGMultiRegionGrowingSystem_H
