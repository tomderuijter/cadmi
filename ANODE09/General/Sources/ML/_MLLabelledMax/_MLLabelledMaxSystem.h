//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-05-21
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledMaxSystem_H
#define ___MLLabelledMaxSystem_H


// DLL export macro definition.
#ifdef _MLLABELLEDMAX_EXPORTS
  // Use the _MLLABELLEDMAX_EXPORT macro to export classes and functions.
  #define _MLLABELLEDMAX_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLLABELLEDMAX_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLLabelledMaxSystem_H
