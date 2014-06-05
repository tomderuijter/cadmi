//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Wieke
// \date    2014-06-05
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGPixelCoordinatesSystem_H
#define __DIAGPixelCoordinatesSystem_H


// DLL export macro definition.
#ifdef DIAGPIXELCOORDINATES_EXPORTS
  // Use the DIAGPIXELCOORDINATES_EXPORT macro to export classes and functions.
  #define DIAGPIXELCOORDINATES_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define DIAGPIXELCOORDINATES_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // __DIAGPixelCoordinatesSystem_H
