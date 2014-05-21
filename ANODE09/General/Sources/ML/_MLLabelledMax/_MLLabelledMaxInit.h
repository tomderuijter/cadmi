//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-05-21
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledMaxInit_H
#define ___MLLabelledMaxInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLLabelledMaxInit();

ML_END_NAMESPACE

#endif // ___MLLabelledMaxInit_H
