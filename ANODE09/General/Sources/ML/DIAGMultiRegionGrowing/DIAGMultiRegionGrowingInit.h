//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-06-27
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
