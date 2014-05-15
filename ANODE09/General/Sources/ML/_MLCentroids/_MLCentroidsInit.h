//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
*/
//----------------------------------------------------------------------------------


#ifndef ___MLCentroidsInit_H
#define ___MLCentroidsInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLCentroidsInit();

ML_END_NAMESPACE

#endif // ___MLCentroidsInit_H
