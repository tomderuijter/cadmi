//----------------------------------------------------------------------------------
//! The ML module output image handle class AxisEdgeMaskOutputImageHandler.
/*!
// \file    
// \author     wieke
// \date    2014-04-23
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlAxisEdgeMaskOutputImageHandler.h"

ML_START_NAMESPACE


AxisEdgeMaskOutputImageHandler::Parameters::Parameters() 
{
  this->front = false;  
  this->back = false;  
  this->right = false;  
  this->left = false;  
  this->top = false;  
  this->bottom = false;  
}

AxisEdgeMaskOutputImageHandler::AxisEdgeMaskOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox AxisEdgeMaskOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


template <typename OUTTYPE>
void AxisEdgeMaskOutputImageHandler::typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    const TSubImage<OUTTYPE>& inputSubImage0,
    UserThreadData* /*userThreadData*/)
{
  // Compute outSubImage from inSubImage[0-N].

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage.getValidRegion();
  bool front = this -> _parameters.front; 
  bool back = this -> _parameters.back; 
  bool right = this -> _parameters.right; 
  bool left = this -> _parameters.left; 
  bool top = this -> _parameters.top; 
  bool bottom = this -> _parameters.bottom; 
  
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
            	if (front  && p.y == validOutBox.v1.y ||
            	    back   && p.y == validOutBox.v2.y ||
            	    right  && p.x == validOutBox.v1.x ||
            	    left   && p.x == validOutBox.v2.x ||
            	    top    && p.z == validOutBox.v2.z ||
            	    bottom && p.z == validOutBox.v1.z)
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
