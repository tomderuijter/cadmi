//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-05-27
*/
//----------------------------------------------------------------------------------


#ifndef ___MLMaskedPixelValuesSystem_H
#define ___MLMaskedPixelValuesSystem_H


// DLL export macro definition.
#ifdef _MLMASKEDPIXELVALUES_EXPORTS
  // Use the _MLMASKEDPIXELVALUES_EXPORT macro to export classes and functions.
  #define _MLMASKEDPIXELVALUES_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLMASKEDPIXELVALUES_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLMaskedPixelValuesSystem_H
