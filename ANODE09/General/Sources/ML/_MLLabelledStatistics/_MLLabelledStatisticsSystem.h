//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-05-16
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledStatisticsSystem_H
#define ___MLLabelledStatisticsSystem_H


// DLL export macro definition.
#ifdef _MLLABELLEDSTATISTICS_EXPORTS
  // Use the _MLLABELLEDSTATISTICS_EXPORT macro to export classes and functions.
  #define _MLLABELLEDSTATISTICS_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLLABELLEDSTATISTICS_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLLabelledStatisticsSystem_H
