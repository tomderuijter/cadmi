//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-05-08
*/
//----------------------------------------------------------------------------------


#ifndef ___MLFilterLabelByVolumeInit_H
#define ___MLFilterLabelByVolumeInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLFilterLabelByVolumeInit();

ML_END_NAMESPACE

#endif // ___MLFilterLabelByVolumeInit_H
