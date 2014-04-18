//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-04-18
*/
//----------------------------------------------------------------------------------


#ifndef ___MLFrontBackMaskInit_H
#define ___MLFrontBackMaskInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLFrontBackMaskInit();

ML_END_NAMESPACE

#endif // ___MLFrontBackMaskInit_H
