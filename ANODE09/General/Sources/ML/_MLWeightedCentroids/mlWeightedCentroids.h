//----------------------------------------------------------------------------------
//! The ML module class WeightedCentroids.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlWeightedCentroids_H
#define __mlWeightedCentroids_H


// Local includes
#include "_MLWeightedCentroidsSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLWEIGHTEDCENTROIDS_EXPORT WeightedCentroids : public Module
{
public:

  //! Constructor.
  WeightedCentroids();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the WeightedCentroidsHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:


  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(WeightedCentroids)
};


ML_END_NAMESPACE

#endif // __mlWeightedCentroids_H