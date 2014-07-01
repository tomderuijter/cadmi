//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author     wieke
// \date    2014-07-01
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGMultiRegionGrowingInit_H
#define __DIAGMultiRegionGrowingInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int DIAGMultiRegionGrowingInit();

ML_END_NAMESPACE

#endif // __DIAGMultiRegionGrowingInit_H
