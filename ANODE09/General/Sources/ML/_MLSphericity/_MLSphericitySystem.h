//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-04-24
*/
//----------------------------------------------------------------------------------


#ifndef ___MLSphericitySystem_H
#define ___MLSphericitySystem_H


// DLL export macro definition.
#ifdef _MLSPHERICITY_EXPORTS
  // Use the _MLSPHERICITY_EXPORT macro to export classes and functions.
  #define _MLSPHERICITY_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLSPHERICITY_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLSphericitySystem_H
