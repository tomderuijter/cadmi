//----------------------------------------------------------------------------------
//! The ML module output image handle class FrontBackMaskOutputImageHandler.
/*!
// \file    
// \author     wieke
// \date    2014-04-18
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlFrontBackMaskOutputImageHandler.h"

ML_START_NAMESPACE


FrontBackMaskOutputImageHandler::Parameters::Parameters() 
{
}

FrontBackMaskOutputImageHandler::FrontBackMaskOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox FrontBackMaskOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


template <typename OUTTYPE>
void FrontBackMaskOutputImageHandler::typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    const TSubImage<OUTTYPE>& inputSubImage0,
    UserThreadData* /*userThreadData*/)
{
  // Compute outSubImage from inSubImage[0-N].

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage.getValidRegion();

  // Process all voxels of the valid region of the output page.
  ImageVector p;
  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

            p.x = validOutBox.v1.x;
            // Get pointers to row starts of input and output sub-images.
            const OUTTYPE* inVoxel0 = inputSubImage0.getImagePointer(p);

            OUTTYPE*  outVoxel = outputSubImage.getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel, ++inVoxel0)
            {
            	if (p.y == validOutBox.v1.y || p.y == validOutBox.v2.y || p.x == validOutBox.v1.x || p.x == validOutBox.v2.x )
	              *outVoxel = *inVoxel0;
	            else
	              *outVoxel = 0;
            }
          }
        }
      }
    }
  }
}

ML_END_NAMESPACE
