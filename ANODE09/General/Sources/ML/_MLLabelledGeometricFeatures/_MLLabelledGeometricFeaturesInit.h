//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-05-21
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledGeometricFeaturesInit_H
#define ___MLLabelledGeometricFeaturesInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLLabelledGeometricFeaturesInit();

ML_END_NAMESPACE

#endif // ___MLLabelledGeometricFeaturesInit_H
