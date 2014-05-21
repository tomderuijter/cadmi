//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-05-21
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledGeometricFeaturesSystem_H
#define ___MLLabelledGeometricFeaturesSystem_H


// DLL export macro definition.
#ifdef _MLLABELLEDGEOMETRICFEATURES_EXPORTS
  // Use the _MLLABELLEDGEOMETRICFEATURES_EXPORT macro to export classes and functions.
  #define _MLLABELLEDGEOMETRICFEATURES_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLLABELLEDGEOMETRICFEATURES_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLLabelledGeometricFeaturesSystem_H
