//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-04-18
*/
//----------------------------------------------------------------------------------


#ifndef ___MLFrontBackMaskSystem_H
#define ___MLFrontBackMaskSystem_H


// DLL export macro definition.
#ifdef _MLFRONTBACKMASK_EXPORTS
  // Use the _MLFRONTBACKMASK_EXPORT macro to export classes and functions.
  #define _MLFRONTBACKMASK_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLFRONTBACKMASK_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLFrontBackMaskSystem_H
