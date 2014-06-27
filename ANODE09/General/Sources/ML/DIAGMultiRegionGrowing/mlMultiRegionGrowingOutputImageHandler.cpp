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

#include "mlMultiRegionGrowingOutputImageHandler.h"
#include <iostream>
#include <vector>

ML_START_NAMESPACE


MultiRegionGrowingOutputImageHandler::Parameters::Parameters() 
{
  this->tolerance = 0.1;  
}

MultiRegionGrowingOutputImageHandler::MultiRegionGrowingOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox MultiRegionGrowingOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


void MultiRegionGrowingOutputImageHandler::typedCalculateOutputSubImage(TSubImage<MLuint32>& outputSubImage,
    const TSubImage<MLfloat>& inputSubImage0,
    const TSubImage<MLuint32>& inputSubImage1,
    UserThreadData* /*userThreadData*/)
{
  // Compute outSubImage from inSubImage[0-N].

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage.getValidRegion();
  float tol = this -> _parameters.tolerance; 
  std::cout << tol << std::endl;
  
  MLuint32 min;
  MLuint32 max;
  
  inputSubImage1.calculateMinMax(min, max, NULL);
  const int nrCandidates = (int) max;
  std::vector<std::vector<float> > startvalue(nrCandidates);
  
  int output[validOutBox.v2.x + 1][validOutBox.v2.y + 1][validOutBox.v2.z + 1]; 
  
  std::cout << validOutBox.v1.x << " " << validOutBox.v2.x << std::endl;
  
  ImageVector p;

  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

            p.x = validOutBox.v1.x;
            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x)
            {
              output[p.x][p.y][p.z] = 0;
            }
          }
        }
      }
    }
  }
  
  // Process all voxels of the valid region of the output page.
  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

            p.x = validOutBox.v1.x;

            MLuint32*  outVoxel = outputSubImage.getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel)
            {
              *outVoxel = 0;//output[p.x - 1][p.y - 1][p.z - 1];
            }
          }
        }
      }
    }
  }
}



ML_END_NAMESPACE
