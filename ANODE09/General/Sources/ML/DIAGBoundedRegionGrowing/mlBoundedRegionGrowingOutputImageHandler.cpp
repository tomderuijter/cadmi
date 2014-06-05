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

#include "mlBoundedRegionGrowingOutputImageHandler.h"

ML_START_NAMESPACE


BoundedRegionGrowingOutputImageHandler::Parameters::Parameters() 
{
  this->lowerBound = -1000;  
  this->upperBound = 500;  
  this->relUpperThreshold = 10;  
  this->relLowerThreshold = 10;  
}

BoundedRegionGrowingOutputImageHandler::BoundedRegionGrowingOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox BoundedRegionGrowingOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


void BoundedRegionGrowingOutputImageHandler::typedCalculateOutputSubImage(TSubImage<MLint32>& outputSubImage,
    const TSubImage<MLint32>& inputSubImage0,
    const TSubImage<MLint32>& /* inputSubImage1 */,
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
            const MLint32* inVoxel0 = inputSubImage0.getImagePointer(p);

            MLint32*  outVoxel = outputSubImage.getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel, ++inVoxel0)
            {
              *outVoxel = *inVoxel0;
            }
          }
        }
      }
    }
  }
}

ML_END_NAMESPACE