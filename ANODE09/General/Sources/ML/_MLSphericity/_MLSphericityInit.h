//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-04-24
*/
//----------------------------------------------------------------------------------


#ifndef ___MLSphericityInit_H
#define ___MLSphericityInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLSphericityInit();

ML_END_NAMESPACE

#endif // ___MLSphericityInit_H
