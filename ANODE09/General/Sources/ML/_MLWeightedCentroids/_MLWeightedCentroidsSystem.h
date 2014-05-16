//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
*/
//----------------------------------------------------------------------------------


#ifndef ___MLWeightedCentroidsSystem_H
#define ___MLWeightedCentroidsSystem_H


// DLL export macro definition.
#ifdef _MLWEIGHTEDCENTROIDS_EXPORTS
  // Use the _MLWEIGHTEDCENTROIDS_EXPORT macro to export classes and functions.
  #define _MLWEIGHTEDCENTROIDS_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLWEIGHTEDCENTROIDS_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLWeightedCentroidsSystem_H
