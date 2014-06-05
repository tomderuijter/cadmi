//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-05-23
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGBoundedRegionGrowingSystem_H
#define __DIAGBoundedRegionGrowingSystem_H


// DLL export macro definition.
#ifdef DIAGBOUNDEDREGIONGROWING_EXPORTS
  // Use the DIAGBOUNDEDREGIONGROWING_EXPORT macro to export classes and functions.
  #define DIAGBOUNDEDREGIONGROWING_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define DIAGBOUNDEDREGIONGROWING_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // __DIAGBoundedRegionGrowingSystem_H
