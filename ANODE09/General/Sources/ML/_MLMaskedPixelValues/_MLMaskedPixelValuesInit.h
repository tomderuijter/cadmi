//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-05-27
*/
//----------------------------------------------------------------------------------


#ifndef ___MLMaskedPixelValuesInit_H
#define ___MLMaskedPixelValuesInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLMaskedPixelValuesInit();

ML_END_NAMESPACE

#endif // ___MLMaskedPixelValuesInit_H
