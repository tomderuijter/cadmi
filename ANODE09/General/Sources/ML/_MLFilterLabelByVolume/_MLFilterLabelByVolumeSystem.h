//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author     wieke
// \date    2014-05-08
*/
//----------------------------------------------------------------------------------


#ifndef ___MLFilterLabelByVolumeSystem_H
#define ___MLFilterLabelByVolumeSystem_H


// DLL export macro definition.
#ifdef _MLFILTERLABELBYVOLUME_EXPORTS
  // Use the _MLFILTERLABELBYVOLUME_EXPORT macro to export classes and functions.
  #define _MLFILTERLABELBYVOLUME_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define _MLFILTERLABELBYVOLUME_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // ___MLFilterLabelByVolumeSystem_H
