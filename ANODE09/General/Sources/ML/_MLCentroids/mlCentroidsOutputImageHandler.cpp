//----------------------------------------------------------------------------------
//! The ML module output image handle class CentroidsOutputImageHandler.
/*!
// \file    
// \author     wieke
// \date    2014-03-03
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlCentroidsOutputImageHandler.h"
#include <iostream>
#include <vector>
ML_START_NAMESPACE


CentroidsOutputImageHandler::Parameters::Parameters() 
{
}

CentroidsOutputImageHandler::CentroidsOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}

SubImageBox CentroidsOutputImageHandler::calculateInputSubImageBox (int /* inputIndex */, const SubImageBox& outputSubImageBox)
{
  // Return region of input image inputIndex needed to compute region
  // outputSubImageBox of output image outputIndex.
  return outputSubImageBox;
}


template <typename OUTTYPE>
void CentroidsOutputImageHandler::typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    const TSubImage<OUTTYPE>& inputSubImage0,
    UserThreadData* /*userThreadData*/)
{

  // Compute outSubImage from inSubImage[0-N].

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage.getValidRegion();
  
  OUTTYPE min;
  OUTTYPE max;
  
  inputSubImage0.calculateMinMax(min, max, NULL);
  
  std::vector<MLint> x((int)max + 1);
  std::vector<MLint> y((int)max + 1);
  std::vector<MLint> z((int)max + 1);
  std::vector<MLint> n((int)max + 1);
  std::vector<OUTTYPE> labels((int)max + 1);
  
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
	          for (; p.x <= rowEnd;  ++p.x, ++inVoxel0, ++outVoxel)
	          {
							x[*inVoxel0]+=p.x;
							y[*inVoxel0]+=p.y;
							z[*inVoxel0]+=p.z;
							labels[*inVoxel0] = *inVoxel0;
							n[*inVoxel0]++;		
							*outVoxel = 0;
	          }
	        }
	      }
	    }
	  }
	}
	

	for (int i = 0; i < max + 1; i++){
		if (n[i] > 0)
		{
			x[i] = x[i] / n[i];
			y[i] = y[i] / n[i];
			z[i] = z[i] / n[i];
		}
	}
	
  for (int i = 1; i < max + 1; i++)
  {  
    p.c = 0;
    p.t = 0;
    p.u = 0;
    p.x = x[i];
    p.y = y[i];
    p.z = z[i];
    OUTTYPE*  outVoxel = outputSubImage.getImagePointer(p);
		*outVoxel = labels[i];
  }
	
}

ML_END_NAMESPACE
