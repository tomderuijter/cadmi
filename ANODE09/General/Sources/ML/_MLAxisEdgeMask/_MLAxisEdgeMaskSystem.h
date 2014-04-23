//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-04-23
*/
//----------------------------------------------------------------------------------


#ifndef ___MLAxisEdgeMaskSystem_H
#define ___MLAxisEdgeMaskSystem_H


// DLL export macro definition.
#ifdef _MLAXISEDGEMASK_EXPORTS
  // Use the _MLAXISEDGEMASK_EXPORT macro to export classes and functions.
  #define _MLAXISEDGEMASK_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLAXISEDGEMASK_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLAxisEdgeMaskSystem_H
