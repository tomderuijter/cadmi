//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-06-05
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGPixelCoordinatesInit_H
#define __DIAGPixelCoordinatesInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int DIAGPixelCoordinatesInit();

ML_END_NAMESPACE

#endif // __DIAGPixelCoordinatesInit_H
