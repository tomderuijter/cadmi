//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Wieke
// \date    2014-05-23
*/
//----------------------------------------------------------------------------------


#ifndef __DIAGBoundedRegionGrowingInit_H
#define __DIAGBoundedRegionGrowingInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int DIAGBoundedRegionGrowingInit();

ML_END_NAMESPACE

#endif // __DIAGBoundedRegionGrowingInit_H
