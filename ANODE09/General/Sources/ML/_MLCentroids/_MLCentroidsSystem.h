//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
*/
//----------------------------------------------------------------------------------


#ifndef ___MLCentroidsSystem_H
#define ___MLCentroidsSystem_H


// DLL export macro definition.
#ifdef _MLCENTROIDS_EXPORTS
  // Use the _MLCENTROIDS_EXPORT macro to export classes and functions.
  #define _MLCENTROIDS_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLCENTROIDS_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLCentroidsSystem_H
