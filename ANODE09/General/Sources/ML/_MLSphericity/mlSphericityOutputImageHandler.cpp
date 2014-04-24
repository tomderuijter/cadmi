//----------------------------------------------------------------------------------
//! The ML module output image handle class SphericityOutputImageHandler.
/*!
// \file    
// \author  Wieke
// \date    2014-04-24
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlSphericityOutputImageHandler.h"
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

ML_START_NAMESPACE


SphericityOutputImageHandler::Parameters::Parameters() 
{
  this->threshold = 0;  
}

SphericityOutputImageHandler::SphericityOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox SphericityOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


template <typename OUTTYPE>
void SphericityOutputImageHandler::typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    const TSubImage<OUTTYPE>& inputSubImage0,
    const TSubImage<OUTTYPE>&  inputSubImage1,
    UserThreadData* /*userThreadData*/)
{
// Compute outSubImage from inSubImage[0-N].

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage.getValidRegion();

  float threshold = this -> _parameters.threshold;
  
  OUTTYPE min;
  OUTTYPE max;
  
  inputSubImage0.calculateMinMax(min, max, NULL);
  
  std::vector<float> area((int)max - 1);
  std::vector<float> perimiter((int)max - 1);
  
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
	          const OUTTYPE* inVoxel1 = inputSubImage1.getImagePointer(p);
	          
	          const MLint rowEnd   = validOutBox.v2.x;

	          // Process all row voxels.
	          for (; p.x <= rowEnd;  ++p.x, ++inVoxel0, ++inVoxel1)
	          {
	          	for(int label = 1; label <= max; label++)
	          	{
          	    area[label - 1] += *inVoxel0 == label;
          	    perimiter[label - 1] += *inVoxel1 == label;
	            }
	          }
	        }
	      }
	    }
	  }
	}
	
	std::vector<float> circularity((int)max - 1);
	std::vector<int> label((int)max - 1);
	int lbl = 1;
	for (int i = 0; i < max; i++){
		circularity[i] = (pow(M_PI, 1/3)*pow(6*area[i],2/3))/perimiter[i]);
		if (circularity[i] > threshold)
		{
			label[i] = lbl++;
		}
		else
		{
			label[i] = 0;		
		}
	}	
	
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
	          	*outVoxel = 0;
	          	if (*inVoxel0 != 0)
	          	{
	            	*outVoxel = label[(int)*inVoxel0 - 1];
	            }
	          }
	        }
	      }
	    }
	  }
	}
}

ML_END_NAMESPACE
