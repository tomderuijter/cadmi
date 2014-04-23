//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-04-23
*/
//----------------------------------------------------------------------------------


#ifndef ___MLAxisEdgeMaskInit_H
#define ___MLAxisEdgeMaskInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLAxisEdgeMaskInit();

ML_END_NAMESPACE

#endif // ___MLAxisEdgeMaskInit_H
