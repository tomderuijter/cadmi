//----------------------------------------------------------------------------------
//! The ML module output image handle class MultiRegionGrowingOutputImageHandler.
/*!
// \file    
// \author  Wieke
// \date    2014-06-27
//
// 
*/
//----------------------------------------------------------------------------------

#ifndef __mlMultiRegionGrowingOutputImageHandler_H
#define __mlMultiRegionGrowingOutputImageHandler_H

#include <mlTypedHandlers.h>

ML_START_NAMESPACE

//! The MultiRegionGrowingOutputImageHandler handles the page calculation of an output image of MultiRegionGrowing.
//! It should receive all required state from its caller in its
//! constructor and should not keep a reference to the output image nor the module itself.
//! This facilitates to implement a thread safe handler, which does not access non-thread safe shared data,
//! and which can be easily reused by other modules or within other contexts.
class MultiRegionGrowingOutputImageHandler : public TypedCalculateOutputImageHandler<MultiRegionGrowingOutputImageHandler,
    /* numInputs = */ 2>
{

public:
  //! Struct for processing parameters
  struct Parameters 
  {
    MLfloat tolerance; //!< Tolerance
  
    //! Default constructor ensuring that all variables are initialized.
    Parameters();
  };
  
  //! Template configuration of the output/input sub-images.
  enum {
    OutputSubImage_Type = MLuint32Type,
    InputSubImage0_Type = MLfloatType,
    InputSubImage1_Type = MLuint32Type,
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
  MultiRegionGrowingOutputImageHandler(MLint outputIndex, const Parameters& parameters);
  
  //----------------------------------------------------------------------------------
  //! Returns the input image region required to calculate a region of an output image.
  //----------------------------------------------------------------------------------
  SubImageBox calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox);

  //----------------------------------------------------------------------------------
  //! Templated output page calculation: compute output sub-image from input sub-image(s)
  //----------------------------------------------------------------------------------
void typedCalculateOutputSubImage(TSubImage<MLuint32>& outputSubImage,
    const TSubImage<MLfloat>& inputSubImage0,
    const TSubImage<MLuint32>& inputSubImage1,
    UserThreadData* /*userThreadData*/);


bool check(std::vector<std::vector<std::vector<int> > > & image,
  const TSubImage<MLfloat>& inputSubImage0,
  int width,
  int depth,
  int height,
  int x,
  int y,
  int z,
  float tolerance,
  std::vector<float> startValue,
  std::vector<int> & size);

bool grow(std::vector<std::vector<std::vector<int> > > & image,
  const TSubImage<MLfloat>& inputSubImage0,
  int x,
  int y,
  int z,
  float tolerance,
  int label,
  std::vector<float> startValue);
};


ML_END_NAMESPACE

#endif
