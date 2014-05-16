//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-05-16
*/
//----------------------------------------------------------------------------------


#ifndef ___MLLabelledStatisticsInit_H
#define ___MLLabelledStatisticsInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int _MLLabelledStatisticsInit();

ML_END_NAMESPACE

#endif // ___MLLabelledStatisticsInit_H
