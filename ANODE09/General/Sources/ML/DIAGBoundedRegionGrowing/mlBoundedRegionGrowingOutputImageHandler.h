//----------------------------------------------------------------------------------
//! The ML module output image handle class BoundedRegionGrowingOutputImageHandler.
/*!
// \file    
// \author  Wieke
// \date    2014-05-23
//
// 
*/
//----------------------------------------------------------------------------------

#ifndef __mlBoundedRegionGrowingOutputImageHandler_H
#define __mlBoundedRegionGrowingOutputImageHandler_H

#include <mlTypedHandlers.h>

ML_START_NAMESPACE

//! The BoundedRegionGrowingOutputImageHandler handles the page calculation of an output image of BoundedRegionGrowing.
//! It should receive all required state from its caller in its
//! constructor and should not keep a reference to the output image nor the module itself.
//! This facilitates to implement a thread safe handler, which does not access non-thread safe shared data,
//! and which can be easily reused by other modules or within other contexts.
class BoundedRegionGrowingOutputImageHandler : public TypedCalculateOutputImageHandler<BoundedRegionGrowingOutputImageHandler,
    /* numInputs = */ 2>
{

public:
  //! Struct for processing parameters
  struct Parameters 
  {
    MLint lowerBound; //!< Lower Bound
    MLint upperBound; //!< Upper Bound
    MLint relUpperThreshold; //!< Relative Upper Threshold
    MLint relLowerThreshold; //!< Relative Lower Threshold
  
    //! Default constructor ensuring that all variables are initialized.
    Parameters();
  };
  
  //! Template configuration of the output/input sub-images.
  enum {
    OutputSubImage_Type = MLint32Type,
    InputSubImage0_Type = MLint32Type,
    InputSubImage1_Type = MLint32Type,
    InputSubImage0_ReadOnly = true,
    InputSubImage1_ReadOnly = true
  };

private:
  //! Output index: Range depends on the number of output images/modes. 
  //! The first output image/mode has index 0.
  MLint _outputIndex;  
  //! Processing parameter set
  Parameters _parameters;

public:
  //----------------------------------------------------------------------------------
  //! Construct a new handler for given \p outputImage and given module state.
  //! Do not keep references to the outputImage or the module, the needed state
  //! is copied instead.
  //----------------------------------------------------------------------------------
  BoundedRegionGrowingOutputImageHandler(MLint outputIndex, const Parameters& parameters);
  
  //----------------------------------------------------------------------------------
  //! Returns the input image region required to calculate a region of an output image.
  //----------------------------------------------------------------------------------
  SubImageBox calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox);

  //----------------------------------------------------------------------------------
  //! Templated output page calculation: compute output sub-image from input sub-image(s)
  //----------------------------------------------------------------------------------
void typedCalculateOutputSubImage(TSubImage<MLint32>& outputSubImage,
    const TSubImage<MLint32>& inputSubImage0,
    const TSubImage<MLint32>& inputSubImage1,
    UserThreadData* /*userThreadData*/);
};

ML_END_NAMESPACE

#endif