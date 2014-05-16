//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
*/
//----------------------------------------------------------------------------------


#ifndef ___MLWeightedCentroidsInit_H
#define ___MLWeightedCentroidsInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLWeightedCentroidsInit();

ML_END_NAMESPACE

#endif // ___MLWeightedCentroidsInit_H
