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
#include <cmath>

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
  float tolerance = this -> _parameters.tolerance; 
  
  MLuint32 min;
  MLuint32 max;
  
  inputSubImage1.calculateMinMax(min, max, NULL);

  const int nrCandidates = (int) max;
  std::vector<float> startvalue(nrCandidates);
  std::vector<int> size(nrCandidates, 1);

  int limit = 30;
  
  int width = validOutBox.v2.x + 1;
  int depth = validOutBox.v2.y + 1;
  int height = validOutBox.v2.z + 1;

  std::vector<std::vector<std::vector<int> > > output;

  output.resize(width);
	for(int i=0;i<width;i++)
	{
		output[i].resize(depth);
		for(int j=0;j<depth;j++)
		{
		   output[i][j].resize(height, 0);
		}
	}

  ImageVector p;
  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

	        	p.x = validOutBox.v1.x;
            const MLint rowEnd   = validOutBox.v2.x;
			
						const MLuint32* inVoxel1 = inputSubImage1.getImagePointer(p);
            const MLfloat* inVoxel0 = inputSubImage0.getImagePointer(p);
            
            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++inVoxel1, ++inVoxel0)
            {
              output[p.x][p.y][p.z] = *inVoxel1;
              if (*inVoxel1 > 0)
              {
                startvalue[*inVoxel1 - 1] = *inVoxel0;
              }
            }
          }
        }
      }
    }
  }

  //check(output, inputSubImage0, width, depth, height, x, y, z, tolerance, startvalue);
  
  bool change = true;
  while (change){
    change = false;
    std::vector<std::vector<std::vector<int> > > outputold = output;
    
    for (int x = 0; x < width; x++)
      for (int y = 0; y < depth; y++)
        for (int z = 0; z < height; z++)
        {
          if (outputold[x][y][z] > 0)
            if (size[outputold[x][y][z]-1] < limit)
              if (check(output, inputSubImage0, width, depth, height, x, y, z, tolerance, startvalue, size))
                change = true;
        }
    
  }

  for(int i = 0; i < max; i++)
    std::cout << "size[" << i << "]=" << size[i] << std::endl;

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
              *outVoxel = output[p.x][p.y][p.z];
            }
          }
        }
      }
    }
  }
}

bool MultiRegionGrowingOutputImageHandler::check(std::vector<std::vector<std::vector<int> > > & image,
  const TSubImage<MLfloat>& inputSubImage0,
  int width,
  int depth,
  int height,
  int x,
  int y,
  int z,
  float tolerance,
  std::vector<float> startValue,
  std::vector<int> & size)
{

  // Figure out neighbor bounds
  bool change = false;
  int label = image[x][y][z];
  if (x > 0)
  {
      if (grow(image, inputSubImage0, x -1, y, z, tolerance, label, startValue))
      {
        change = true;
        size[label-1] = size[label-1] + 1;
      }
  }
  if (x < (width -1))
  {
    if (grow(image, inputSubImage0, x +1, y, z, tolerance, label, startValue))
    {
      change = true;
      size[label-1] = size[label-1] + 1;
    }
  }
  if (y > 0)
  {
    if (grow(image, inputSubImage0, x, y -1, z, tolerance, label, startValue))
    {
      change = true;
      size[label-1] = size[label-1] + 1;
    }
  }
  if (y < (depth -1))
  {
    if (grow(image, inputSubImage0, x, y +1, z, tolerance, label, startValue))
    {
      change = true;
      size[label-1] = size[label-1] + 1;
    }
  }
  if (z > 0)
  {
    if (grow(image, inputSubImage0, x, y, z -1, tolerance, label, startValue))
    {
      change = true;
      size[label-1] = size[label-1] + 1;
    }
  }
  if (z < (height -1))
  {
    if (grow(image, inputSubImage0, x, y, z +1, tolerance, label, startValue))
    {
      change = true;
      size[label-1] = size[label-1] + 1;
    }
  }
  return change;
}

bool MultiRegionGrowingOutputImageHandler::grow(std::vector<std::vector<std::vector<int> > > & image,
  const TSubImage<MLfloat>& inputSubImage0,
  int x,
  int y,
  int z,
  float tolerance,
  int label,
  std::vector<float> startValue)
{
  if(image[x][y][z] > 0)
    return false;

  ImageVector p;
  p.u = 0;
  p.t = 0;
  p.c = 0;
  p.z = z;
  p.y = y;
  p.x = x;

  const MLfloat* inVoxel = inputSubImage0.getImagePointer(p);
  float diff = std::abs(1 - *inVoxel / startValue[label - 1]);

  if (diff < tolerance)
  {
    image[x][y][z] = label;
    return true;
  }
  else
    return false;

}
ML_END_NAMESPACE
